## mm: cma: NUMA node interface

- NUMA 노드에서 cma에 대한 interfaces를 만들어 주는 패치 인것 같다

```
I've noticed that there is no interfaces exposed by CMA which would let me
to declare contigous memory on particular NUMA node.

This patchset adds the ability to try to allocate contiguous memory on
specific node.  It will fallback to other nodes if the specified one
doesn't work.

Implement a new method for declaring contigous memory on particular node
and keep cma_declare_contiguous() as a wrapper.
```

- nid(node ID)에 대해 적용할 수 있도록 cma_declare_contiguous_nid() 함수를 수정

```
intclude/linux/cma.h

-extern int __init cma_declare_contiguous(phys_addr_t base,
+extern int __init cma_declare_contiguous_nid(phys_addr_t base,
 			phys_addr_t size, phys_addr_t limit,
 			phys_addr_t alignment, unsigned int order_per_bit,
-			bool fixed, const char *name, struct cma **res_cma);
+			bool fixed, const char *name, struct cma **res_cma,
+			int nid);
+static inline int __init cma_declare_contiguous(phys_addr_t base,
+			phys_addr_t size, phys_addr_t limit,
+			phys_addr_t alignment, unsigned int order_per_bit,
+			bool fixed, const char *name, struct cma **res_cma)
+{
+	return cma_declare_contiguous_nid(base, size, limit, alignment,
+			order_per_bit, fixed, name, res_cma, NUMA_NO_NODE);
+}
```

- memblock에서도 nid에 대한 내용을 추가 해줌

```
+++ a/include/linux/memblock.h
@@ -348,6 +348,9 @@ static inline int memblock_get_region_no
 
+phys_addr_t memblock_alloc_range_nid(phys_addr_t size,
+				      phys_addr_t align, phys_addr_t start,
+				      phys_addr_t end, int nid, bool exact_nid);
```

* memblock_alloc_range_nid() 함수를 사용하도록 cma_declare_contiguous_nid() 함수를 수정

```
--- a/mm/cma.c~mm-cma-numa-node-interface
+++ a/mm/cma.c
@@ -220,7 +220,7 @@ int __init cma_init_reserved_mem(phys_ad
 }
 
 /**
- * cma_declare_contiguous() - reserve custom contiguous area
+ * cma_declare_contiguous_nid() - reserve custom contiguous area
  * @base: Base address of the reserved area optional, use 0 for any
  * @size: Size of the reserved area (in bytes),
  * @limit: End address of the reserved memory (optional, 0 for any).
@@ -229,6 +229,7 @@ int __init cma_init_reserved_mem(phys_ad
  * @fixed: hint about where to place the reserved area
  * @name: The name of the area. See function cma_init_reserved_mem()
  * @res_cma: Pointer to store the created cma region.
+ * @nid: nid of the free area to find, %NUMA_NO_NODE for any node
  *
  * This function reserves memory from early allocator. It should be
  * called by arch specific code once the early allocator (memblock or bootmem)
@@ -238,10 +239,11 @@ int __init cma_init_reserved_mem(phys_ad
  * If @fixed is true, reserve contiguous area at exactly @base.  If false,
  * reserve in range from @base to @limit.
  */
-int __init cma_declare_contiguous(phys_addr_t base,
+int __init cma_declare_contiguous_nid(phys_addr_t base,
 			phys_addr_t size, phys_addr_t limit,
 			phys_addr_t alignment, unsigned int order_per_bit,
-			bool fixed, const char *name, struct cma **res_cma)
+			bool fixed, const char *name, struct cma **res_cma,
+			int nid)
 {
 	phys_addr_t memblock_end = memblock_end_of_DRAM();
 	phys_addr_t highmem_start;
@@ -336,14 +338,14 @@ int __init cma_declare_contiguous(phys_a
 		 * memory in case of failure.
 		 */
 		if (base < highmem_start && limit > highmem_start) {
-			addr = memblock_phys_alloc_range(size, alignment,
-							 highmem_start, limit);
+			addr = memblock_alloc_range_nid(size, alignment,
+					highmem_start, limit, nid, false);
 			limit = highmem_start;
 		}
 
 		if (!addr) {
-			addr = memblock_phys_alloc_range(size, alignment, base,
-							 limit);
+			addr = memblock_alloc_range_nid(size, alignment, base,
+					limit, nid, false);
 			if (!addr) {
 				ret = -ENOMEM;
 				goto err;
```

```
--- a/mm/memblock.c~mm-cma-numa-node-interface
+++ a/mm/memblock.c
@@ -1349,7 +1349,7 @@ __next_mem_pfn_range_in_zone(u64 *idx, s
  * Return:
  * Physical address of allocated memory block on success, %0 on failure.
  */
-static phys_addr_t __init memblock_alloc_range_nid(phys_addr_t size,
+phys_addr_t __init memblock_alloc_range_nid(phys_addr_t size,
 					phys_addr_t align, phys_addr_t start,
 					phys_addr_t end, int nid,
 					bool exact_nid)
```

