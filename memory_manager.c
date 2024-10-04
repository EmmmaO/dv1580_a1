#include "memory_manager.h"

typedef struct memoryBlock
{
    size_t size;
    bool is_free;
    struct memoryBlock* nextBlock;
   // struct memoryBlock* prevBlock;
}memoryBlock;

memoryBlock* memoryPool = NULL;
size_t poolSize = 0;
size_t allocatedSize = 0;
void* memory_address;

void mem_init(size_t size)
{
    memory_address = malloc(size*sizeof(memoryBlock));
    printf("\nInitialized: %ld\n", size*sizeof(memoryBlock));
    if(!memory_address)
    {
        printf("Memory initializing failed!\n");
        exit(EXIT_FAILURE);
    }
    memoryPool = (memoryBlock*)((char*)memory_address);
    memoryPool->size = size*sizeof(memoryBlock);
    printf("memoryPool->size: %ld, size: %ld, sizeof(memoryBlock): %ld\n", memoryPool->size, size, sizeof(memoryBlock));
    memoryPool->is_free = true;
    memoryPool->nextBlock = NULL;
    poolSize = size*sizeof(memoryBlock);
    printf("Memory initialized!\n\n");
}

void* mem_alloc(size_t size)
{
    printf("Trying to allocate: %ld (total: %ld) has: %ld left\n", size, allocatedSize+size, poolSize/sizeof(memoryBlock)-allocatedSize);
    
    if (poolSize >= sizeof(memoryBlock)*(allocatedSize + size))
    {
        memoryBlock* current = memoryPool;
        while(current)
        {
            printf("current block size: %ld\n", current->size/sizeof(memoryBlock));
            if (current->is_free && size*sizeof(memoryBlock) <= current->size || current->size == 0)
            {
                //Splites the block if there is memory left
                if (current->size > size + sizeof(memoryBlock))
                {
                    memoryBlock* newMemBlock = (memoryBlock*)((char*)current+sizeof(memoryBlock)+size);
                    newMemBlock->size = current->size - size*sizeof(memoryBlock);            
                    //newMemBlock->size = poolSize - sizeof(memoryBlock)*(allocatedSize - size);
                    newMemBlock->is_free = true;
                    newMemBlock->nextBlock = current->nextBlock;
                    //newMemBlock->prevBlock = current;

                  //  printf("nmb.s: %ld\n", (newMemBlock->size)/sizeof(memoryBlock));

                    current->size = size*sizeof(memoryBlock);
                    current->nextBlock = newMemBlock;
                    printf("Memory block split!\n");
                    printf("Current: %ld  nextBlock: %ld\n", current->size/sizeof(memoryBlock), newMemBlock->size/sizeof(memoryBlock));
                }
                current->is_free = false;
                printf("Memory allocated!\n\n");
                allocatedSize += size;// + sizeof(memoryBlock);
              //  printf("Allocated size: %ld\n", allocatedSize);
                return (void*)((char*)current + sizeof(memoryBlock));
            }
            current = current->nextBlock;
        }
    }
    else
    {
        printf("Trying to allocate %ld (total %ld), but only have %ld left.\n", size, allocatedSize+size, (poolSize)/sizeof(memoryBlock) - allocatedSize);
        printf("Not enought space! Allocation failed!\n");
        printf("Failed to allocate memory!\n\n");
    }
    return NULL;
}

void mem_free(void* block)
{
    if (!block)
    {
        printf("Cannot free null block\n");
        return;
    }
    
    memoryBlock *thisblock = (memoryBlock*)((char*)block - sizeof(memoryBlock));
    thisblock->is_free = true;
    allocatedSize -= thisblock->size/sizeof(memoryBlock);

    memoryBlock *current = memoryPool;
    printf("Memory block freed (freed: %ld)  have: %ld left\n\n", thisblock->size/sizeof(memoryBlock), poolSize/sizeof(memoryBlock) - allocatedSize);    

    while(current)
    {
        if(current->nextBlock)
        {
            if(current->is_free && current->nextBlock->is_free)
            {
                current->size += current->nextBlock->size;
                current->nextBlock = current->nextBlock->nextBlock;
            }
        }
        current = current->nextBlock;
    }

}

void* mem_resize(void* block, size_t size)
{
    if(!block)
    {
        printf("Can't resize a non-existing block!");
        return NULL;
    }

    memoryBlock* walker = (memoryBlock*)((char*)block - sizeof(memoryBlock));
    

    memoryBlock* newBlock = mem_alloc(size);
    if(newBlock)
    {
        size_t copy_size = (walker->size < size) ? walker->size : size;
        memcpy(newBlock,block,copy_size);
        mem_free(block);
    }
    return newBlock;

}

void mem_deinit()
{
    if(memory_address)
    {
        free(memory_address);
        memoryPool = NULL;
        memory_address = NULL;   
        poolSize = 0;
    }
}

// int main()
// {
//     mem_init(1024);
//     mem_alloc(500);
//     mem_alloc(300);
//     mem_alloc(200);

//     printf("Memory pool size: %zu\n", memoryPool->size);
//     printf("Pool size: %ld\n", poolSize);
//     printf("Alloxated size: %ld\n", allocatedSize);

//     return 0;
// }
