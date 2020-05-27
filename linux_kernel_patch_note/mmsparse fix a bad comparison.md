## mm/sparse: fix a bad comparison



| author    | ![img](https://seccdn.libravatar.org/avatar/1219e92b0863743e87ad67f81c236416?s=13&d=retro)Qian Cai <cai@lca.pw> | 2019-03-05 15:50:11 -0800 |
| :-------- | ------------------------------------------------------------ | ------------------------- |
| committer | ![img](https://seccdn.libravatar.org/avatar/cbd18395260b6be2575187286a262f9a?s=13&d=retro)Greg Kroah-Hartman <gregkh@linuxfoundation.org> | 2019-04-05 22:32:58 +0200 |
| commit    | [7b287c47e4524bdc73152d77a68c68a044b9c111](https://source.codeaurora.org/quic/la/kernel/msm-4.19/commit/?h=korg/linux-4.19.y&id=7b287c47e4524bdc73152d77a68c68a044b9c111) ([patch](https://source.codeaurora.org/quic/la/kernel/msm-4.19/patch/?id=7b287c47e4524bdc73152d77a68c68a044b9c111)) |                           |
| tree      | [30e0c27222c35c5d3734e8241bc0d0ee9e1f2308](https://source.codeaurora.org/quic/la/kernel/msm-4.19/tree/?h=korg/linux-4.19.y&id=7b287c47e4524bdc73152d77a68c68a044b9c111) |                           |
| parent    | [aea8c971b9c5f7567d2f4ea9e932b8a82679a037](https://source.codeaurora.org/quic/la/kernel/msm-4.19/commit/?h=korg/linux-4.19.y&id=aea8c971b9c5f7567d2f4ea9e932b8a82679a037) ([diff](https://source.codeaurora.org/quic/la/kernel/msm-4.19/diff/?h=korg/linux-4.19.y&id=7b287c47e4524bdc73152d77a68c68a044b9c111&id2=aea8c971b9c5f7567d2f4ea9e932b8a82679a037)) |                           |

### ## 커밋 내용을 보면, 빌드하다가 warning 메세지를 분석해서 그것을 고친 것으로 보임##

* next_present_section_nr()은 -1을 반환할 경우가 있는데,  section_nr이 unsigned라면 section_nr>=0이 항상 참이되므로 명시적으로 -1을 확인해줘야 한다.

```
[ Upstream commit d778015ac95bc036af73342c878ab19250e01fe1 ]

next_present_section_nr() could only return an unsigned number -1, so
just check it specifically where compilers will convert -1 to unsigned
if needed.

  mm/sparse.c: In function 'sparse_init_nid':
  mm/sparse.c:200:20: warning: comparison of unsigned expression >= 0 is always true [-Wtype-limits]
         ((section_nr >= 0) &&    \
                      ^~
  mm/sparse.c:478:2: note: in expansion of macro
  'for_each_present_section_nr'
    for_each_present_section_nr(pnum_begin, pnum) {
    ^~~~~~~~~~~~~~~~~~~~~~~~~~~
  mm/sparse.c:200:20: warning: comparison of unsigned expression >= 0 is always true [-Wtype-limits]
         ((section_nr >= 0) &&    \
                      ^~
  mm/sparse.c:497:2: note: in expansion of macro
  'for_each_present_section_nr'
    for_each_present_section_nr(pnum_begin, pnum) {
    ^~~~~~~~~~~~~~~~~~~~~~~~~~~
  mm/sparse.c: In function 'sparse_init':
  mm/sparse.c:200:20: warning: comparison of unsigned expression >= 0 is always true [-Wtype-limits]
         ((section_nr >= 0) &&    \
                      ^~
  mm/sparse.c:520:2: note: in expansion of macro
  'for_each_present_section_nr'
    for_each_present_section_nr(pnum_begin + 1, pnum_end) {
    ^~~~~~~~~~~~~~~~~~~~~~~~~~~

Link: http://lkml.kernel.org/r/20190228181839.86504-1-cai@lca.pw
Fixes: c4e1be9ec113 ("mm, sparsemem: break out of loops early")
Signed-off-by: Qian Cai <cai@lca.pw>
Reviewed-by: Andrew Morton <akpm@linux-foundation.org>
Cc: Dave Hansen <dave.hansen@linux.intel.com>
Signed-off-by: Andrew Morton <akpm@linux-foundation.org>
Signed-off-by: Linus Torvalds <torvalds@linux-foundation.org>
Signed-off-by: Sasha Levin <sashal@kernel.org>
```



* for_each_present_section_nr() 매크로에서 section_nr >= 0 인 부분을 section_nr != -1로 바꿔줌!

```
diff --git a/mm/sparse.c b/mm/sparse.c
index 10b07ee..45950a0 100644
--- a/mm/sparse.c
+++ b/mm/sparse.c
@@ -196,7 +196,7 @@ static inline int next_present_section_nr(int section_nr)
 }
 #define for_each_present_section_nr(start, section_nr)		\
 	for (section_nr = next_present_section_nr(start-1);	\
-	     ((section_nr >= 0) &&				\
+	     ((section_nr != -1) &&				\
 	      (section_nr <= __highest_present_section_nr));	\
 	     section_nr = next_present_section_nr(section_nr))
```



* next_present_section_nr() 함수

```
203 static inline int next_present_section_nr(int section_nr)
204 {
205     do {
206         section_nr++;
207         if (present_section_nr(section_nr))
208             return section_nr;
209     } while ((section_nr <= __highest_present_section_nr));
210 
211     return -1;
212 }
```

- 206~208줄에서 인자로 들어온 section_nr에 +1하여 section_nr이 present한지 확인
- __highest_present_section_nr까지 확인하고, present한 section_nr이 없으면 -1을 return