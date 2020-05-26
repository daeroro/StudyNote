## **mm, sparse: pass nid instead of pgdat to sparse_add_one_section()**

### ## 구조체 전체를 사용하지 않으면 굳이 구조체 전체를 넘기지 않아도 된다##



| author    | ![img](https://seccdn.libravatar.org/avatar/9a875c635c83bed7b21fe7c08b9e83e7?s=13&d=retro)Wei Yang <richard.weiyang@gmail.com> | 2020-01-28 10:50:00 +0100 |
| :-------- | ------------------------------------------------------------ | ------------------------- |
| committer | ![img](https://seccdn.libravatar.org/avatar/cbd18395260b6be2575187286a262f9a?s=13&d=retro)Greg Kroah-Hartman <gregkh@linuxfoundation.org> | 2020-01-29 16:43:24 +0100 |
| commit    | [aa2e8b68f24462ceb1c495cbde642a174c80fe55](https://source.codeaurora.org/quic/la/kernel/msm-4.19/commit/?h=korg/linux-4.19.y&id=aa2e8b68f24462ceb1c495cbde642a174c80fe55) ([patch](https://source.codeaurora.org/quic/la/kernel/msm-4.19/patch/?id=aa2e8b68f24462ceb1c495cbde642a174c80fe55)) |                           |
| tree      | [b3187806c7682cb82a775f91d92ba89fa05faf8b](https://source.codeaurora.org/quic/la/kernel/msm-4.19/tree/?h=korg/linux-4.19.y&id=aa2e8b68f24462ceb1c495cbde642a174c80fe55) |                           |
| parent    | [b1dbaa19162857eeb8cd751e58394d1c8c34b12e](https://source.codeaurora.org/quic/la/kernel/msm-4.19/commit/?h=korg/linux-4.19.y&id=b1dbaa19162857eeb8cd751e58394d1c8c34b12e) ([diff](https://source.codeaurora.org/quic/la/kernel/msm-4.19/diff/?h=korg/linux-4.19.y&id=aa2e8b68f24462ceb1c495cbde642a174c80fe55&id2=b1dbaa19162857eeb8cd751e58394d1c8c34b12e)) |                           |

* sparse_add_one_section()에 필요한 것은 node id이다
* int node_id를 가지고 있는 struct pglist_data * pgdat를 인자로 넘기는 것 보다 node id를  바로 넘기는 것이 더 좋은 것으로 보인다.

```
commit 4e0d2e7ef14d9e1c900dac909db45263822b824f upstream.

Since the information needed in sparse_add_one_section() is node id to
allocate proper memory, it is not necessary to pass its pgdat.

This patch changes the prototype of sparse_add_one_section() to pass node
id directly.  This is intended to reduce misleading that
sparse_add_one_section() would touch pgdat.

Link: http://lkml.kernel.org/r/20181204085657.20472-2-richard.weiyang@gmail.com
Signed-off-by: Wei Yang <richard.weiyang@gmail.com>
Reviewed-by: David Hildenbrand <david@redhat.com>
Acked-by: Michal Hocko <mhocko@suse.com>
Cc: Dave Hansen <dave.hansen@intel.com>
Cc: Oscar Salvador <osalvador@suse.de>
Signed-off-by: Andrew Morton <akpm@linux-foundation.org>
Signed-off-by: Linus Torvalds <torvalds@linux-foundation.org>
Signed-off-by: David Hildenbrand <david@redhat.com>
Signed-off-by: Greg Kroah-Hartman <gregkh@linuxfoundation.org>
```

* include/linux/memory_hotplug.h의 sparse_add_one_section()의 선언부 struct pglist_data * pgdat를 넘기는 것보다 바로 int nid를 넘기는 것으로 변경

* mm/memory_hotplug.c에서 sparse_add_one_section()을 호출하는 부분에서 nid를 인자로 넘겨줌

* mm/sparse.c에서 sparse_add_one_section() 정의를 변경

  -> 내부에서 호출하는 sparse_index_init(), kmalloc_section_memmap()의 인자로 들어가는 nid를 수정

```
3 files changed, 7 insertions, 7 deletions
diff --git a/include/linux/memory_hotplug.h b/include/linux/memory_hotplug.h
index 6f13a5a..008e528 100644
--- a/include/linux/memory_hotplug.h
+++ b/include/linux/memory_hotplug.h
@@ -335,8 +335,8 @@ extern void move_pfn_range_to_zone(struct zone *zone, unsigned long start_pfn,
 		unsigned long nr_pages, struct vmem_altmap *altmap);
 extern int offline_pages(unsigned long start_pfn, unsigned long nr_pages);
 extern bool is_memblock_offlined(struct memory_block *mem);
-extern int sparse_add_one_section(struct pglist_data *pgdat,
-		unsigned long start_pfn, struct vmem_altmap *altmap);
+extern int sparse_add_one_section(int nid, unsigned long start_pfn,
+				  struct vmem_altmap *altmap);
 extern void sparse_remove_one_section(struct zone *zone, struct mem_section *ms,
 		unsigned long map_offset, struct vmem_altmap *altmap);
 extern struct page *sparse_decode_mem_map(unsigned long coded_mem_map,
diff --git a/mm/memory_hotplug.c b/mm/memory_hotplug.c
index e2e2cf7..c109e3f 100644
--- a/mm/memory_hotplug.c
+++ b/mm/memory_hotplug.c
@@ -255,7 +255,7 @@ static int __meminit __add_section(int nid, unsigned long phys_start_pfn,
 	if (pfn_valid(phys_start_pfn))
 		return -EEXIST;
 
-	ret = sparse_add_one_section(NODE_DATA(nid), phys_start_pfn, altmap);
+	ret = sparse_add_one_section(nid, phys_start_pfn, altmap);
 	if (ret < 0)
 		return ret;
 
diff --git a/mm/sparse.c b/mm/sparse.c
index 9aca9f2..f52e8c3 100644
--- a/mm/sparse.c
+++ b/mm/sparse.c
@@ -661,8 +661,8 @@ static void free_map_bootmem(struct page *memmap)
  * set.  If this is <=0, then that means that the passed-in
  * map was not consumed and must be freed.
  */
-int __meminit sparse_add_one_section(struct pglist_data *pgdat,
-		unsigned long start_pfn, struct vmem_altmap *altmap)
+int __meminit sparse_add_one_section(int nid, unsigned long start_pfn,
+				     struct vmem_altmap *altmap)
 {
 	unsigned long section_nr = pfn_to_section_nr(start_pfn);
 	struct mem_section *ms;
@@ -674,11 +674,11 @@ int __meminit sparse_add_one_section(struct pglist_data *pgdat,
 	 * no locking for this, because it does its own
 	 * plus, it does a kmalloc
 	 */
-	ret = sparse_index_init(section_nr, pgdat->node_id);
+	ret = sparse_index_init(section_nr, nid);
 	if (ret < 0 && ret != -EEXIST)
 		return ret;
 	ret = 0;
-	memmap = kmalloc_section_memmap(section_nr, pgdat->node_id, altmap);
+	memmap = kmalloc_section_memmap(section_nr, nid, altmap);
 	if (!memmap)
 		return -ENOMEM;
 	usemap = __kmalloc_section_usemap();
```



* linux/include/linux/mmzone.h에 정의되어 있는 struct pglist_data

```
635 typedef struct pglist_data {
 636     struct zone node_zones[MAX_NR_ZONES];
 637     struct zonelist node_zonelists[MAX_ZONELISTS];
 638     int nr_zones;
 639 #ifdef CONFIG_FLAT_NODE_MEM_MAP /* means !SPARSEMEM */
 640     struct page *node_mem_map;
 641 #ifdef CONFIG_PAGE_EXTENSION
 642     struct page_ext *node_page_ext;
 643 #endif
 644 #endif
 645 #if defined(CONFIG_MEMORY_HOTPLUG) || defined(CONFIG_DEFERRED_STRUCT_PAGE_INIT)
 646     /*
 647      * Must be held any time you expect node_start_pfn,
 648      * node_present_pages, node_spanned_pages or nr_zones to stay constant.
 649      *
 650      * pgdat_resize_lock() and pgdat_resize_unlock() are provided to
 651      * manipulate node_size_lock without checking for CONFIG_MEMORY_HOTPLUG
 652      * or CONFIG_DEFERRED_STRUCT_PAGE_INIT.
 653      *
 654      * Nests above zone->lock and zone->span_seqlock
 655      */
 656     spinlock_t node_size_lock;
 657 #endif
 658     unsigned long node_start_pfn;
 659     unsigned long node_present_pages; /* total number of physical pages */
 660     unsigned long node_spanned_pages; /* total size of physical page
 661                          range, including holes */
 662     int node_id;
 663     wait_queue_head_t kswapd_wait;
 664     wait_queue_head_t pfmemalloc_wait;
```

* linux/mm/sparse.c의 sparse_add_one_section()

  ```
  726 /*
  727  * returns the number of sections whose mem_maps were properly
  728  * set.  If this is <=0, then that means that the passed-in
  729  * map was not consumed and must be freed.
  730  */
  731 int __meminit sparse_add_one_section(int nid, unsigned long start_pfn,
  732                      struct vmem_altmap *altmap)
  733 {   
  734     unsigned long section_nr = pfn_to_section_nr(start_pfn);
  735     struct mem_section *ms;
  736     struct page *memmap;
  737     unsigned long *usemap;
  738     int ret;
  739     
  740     /*
  741      * no locking for this, because it does its own
  742      * plus, it does a kmalloc
  743      */ 
  744     ret = sparse_index_init(section_nr, nid);
  745     if (ret < 0 && ret != -EEXIST)
  746         return ret;
  747     ret = 0; 
  748     memmap = kmalloc_section_memmap(section_nr, nid, altmap);
  749     if (!memmap)
  750         return -ENOMEM;
  751     usemap = __kmalloc_section_usemap();
  752     if (!usemap) {
  753         __kfree_section_memmap(memmap, altmap);
  754         return -ENOMEM;
  755     }
  756     
  757     ms = __pfn_to_section(start_pfn);
  758     if (ms->section_mem_map & SECTION_MARKED_PRESENT) {
  759         ret = -EEXIST;
  760         goto out;
  761     }
  762 
  763     /*
  764      * Poison uninitialized struct pages in order to catch invalid flags
  765      * combinations.
  766      */
  767     page_init_poison(memmap, sizeof(struct page) * PAGES_PER_SECTION);
  768 
  769     section_mark_present(ms);
  770     sparse_init_one_section(ms, section_nr, memmap, usemap);
  771 
  772 out:
  773     if (ret < 0) {
  774         kfree(usemap);
  775         __kfree_section_memmap(memmap, altmap);
  776     }
  777     return ret;
  778 }
  ```

  