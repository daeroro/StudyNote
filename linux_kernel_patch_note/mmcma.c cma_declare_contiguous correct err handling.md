## **mm/cma.c: cma_declare_contiguous: correct err handling**

| author    | ![img](https://seccdn.libravatar.org/avatar/bd1578dc29252dc0fbe1358b4daf5138?s=13&d=retro)Peng Fan <peng.fan@nxp.com> | 2019-03-05 15:49:50 -0800 |
| :-------- | ------------------------------------------------------------ | ------------------------- |
| committer | ![img](https://seccdn.libravatar.org/avatar/cbd18395260b6be2575187286a262f9a?s=13&d=retro)Greg Kroah-Hartman <gregkh@linuxfoundation.org> | 2019-04-05 22:32:58 +0200 |
| commit    | [f555b008c576819c27959a45dc418318fcc20a95](https://source.codeaurora.org/quic/la/kernel/msm-4.19/commit/?h=korg/linux-4.19.y&id=f555b008c576819c27959a45dc418318fcc20a95) ([patch](https://source.codeaurora.org/quic/la/kernel/msm-4.19/patch/?id=f555b008c576819c27959a45dc418318fcc20a95)) |                           |

* cma_init_reserved_mem() 함수가 실패한 경우에는 미리 memblock에 할당해 놓은 메모리를 free시켜야 한다.

```
In case cma_init_reserved_mem failed, need to free the memblock
allocated by memblock_reserve or memblock_alloc_range.

Quote Catalin's comments:
  https://lkml.org/lkml/2019/2/26/482

Kmemleak is supposed to work with the memblock_{alloc,free} pair and it
ignores the memblock_reserve() as a memblock_alloc() implementation
detail. It is, however, tolerant to memblock_free() being called on
a sub-range or just a different range from a previous memblock_alloc().
So the original patch looks fine to me. FWIW:
```

* cma_init_reserved_mem() 실패 시 err tag로 이동하는 것이 아니라 free_mem를 tag로 하는 goto을 새로 만들어 memblock_free(base, size)로 할당받은 memblock 메모리를 free한다.

```

diff --git a/mm/cma.c b/mm/cma.c
index 4cb7612..bfe9f53 100644
--- a/mm/cma.c
+++ b/mm/cma.c
@@ -353,12 +353,14 @@ int __init cma_declare_contiguous(phys_addr_t base,
 
 	ret = cma_init_reserved_mem(base, size, order_per_bit, name, res_cma);
 	if (ret)
-		goto err;
+		goto free_mem;
 
 	pr_info("Reserved %ld MiB at %pa\n", (unsigned long)size / SZ_1M,
 		&base);
 	return 0;
 
+free_mem:
+	memblock_free(base, size);
 err:
 	pr_err("Failed to reserve %ld MiB\n", (unsigned long)size / SZ_1M);
 	return ret;
```

