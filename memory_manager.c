#include "memory_manager.h"

typedef struct memoryBlock
{
    size_t size;
    bool is_free;
    struct memoryBlock* nextBlock;
}memoryBlock;

memoryBlock* memoryPool = NULL;
size_t poolSize = 0;
size_t allocatedSize = 0;
void* memory_address;


void mem_init(size_t size)
{
    memory_address = malloc(size*sizeof(int));
    if(!memory_address)
    {
        printf("Memory initializing failed!\n");
        exit;
    }
    memoryPool = (memoryBlock*)memory_address;
    memoryPool->size = size - sizeof(memoryBlock);
    memoryPool->is_free = true;
    memoryPool->nextBlock = NULL;
    poolSize = size;
    printf("Memory initialized!\n");
}

void* mem_alloc(size_t size)
{
    memoryBlock* current = memoryPool;
    while(current)
    {
        if (current->is_free && size <= current->size)
        {
            //Splites the block if there is memory left
            if (current->size > size + sizeof(memoryBlock))
            {
                memoryBlock* newMemBlock = (memoryBlock*)((char*)current+sizeof(memoryBlock)+size);
                newMemBlock->size = current->size - size - sizeof(memoryBlock);                
                newMemBlock->is_free = true;
                newMemBlock->nextBlock = current->nextBlock;

                current->size = size;
                current->nextBlock = newMemBlock;
                printf("Memory block split!\n");
            }
            current->is_free = false;
            printf("Memory allocated!\n");
            allocatedSize += size;
            return (void*)((char*)current + sizeof(memoryBlock));
        }
        current = current->nextBlock;
    }
    printf("Failed to allocate memory!\n");
    return NULL;
}

void mem_free(void* block)
{
    memoryBlock *thisblock = block;
    thisblock->is_free = true;
    free(thisblock);
    
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
        memcpy(newBlock,block,walker->size);
        mem_free(block);
    }
    return newBlock;

}

void mem_deinit()
{
    free(memory_address);
    memoryPool = NULL;
    memory_address = NULL;   
    poolSize = 0;
}

int main()
{
    mem_init(1024);
    mem_alloc(500);
    mem_alloc(300);
    mem_alloc(200);

    printf("Memory pool size: %d\n", memoryPool->size);
    printf("Memory pool size: %d\n", poolSize);
    printf("Alloxated size: %d\n", allocatedSize);

    return 0;
}