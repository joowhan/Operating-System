/*
	This program simulates the address translation on paging systems.
	
	Following the instructions, complete the program.

	Compilation:
		gcc hw7_2.c

*/

#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

typedef struct {
	int bits_for_page_number;
	int bits_for_offset;
	int page_table_length;
	int *frame_number;

// The following fields should be computed by ReadPageTable() from the above fields.
	int page_size;
	int limit; 
} PageTable;


int ReadPageTable(const char *filename, PageTable *pt);
void DisplayPageTable(PageTable *pt);
void DestroyPageTable(PageTable *pt);
int Translate(int logical_addr, PageTable *pt);

int main(int argc, char *argv[])
{
	if(argc < 2){
		printf("Usage: %s <pagetable_file>\n", argv[0]);
		return 0;
	}

	PageTable pt = { 0 };
	int ret = ReadPageTable(argv[1], &pt);
	if(ret == FALSE){
		printf("Failed to read page table from %s\n", argv[1]);
		return -1;
	}

	DisplayPageTable(&pt);

	int addr_limit = pt.limit;

	int step = 1;
	if(addr_limit > 256)
		step = addr_limit / 256;

	for(int logical_addr = 0; logical_addr < addr_limit; logical_addr += step){
		int physical_addr = Translate(logical_addr, &pt);
		printf("%04d (0x%04x) ==> %04d (0x%04x)\n", logical_addr, logical_addr, physical_addr, physical_addr);
	}

	DestroyPageTable(&pt);

	return 0;
}

int ReadPageTable(const char *filename, PageTable *pt)
{
	FILE *fp = fopen(filename, "r");
	if(fp == NULL){
		printf("Failed to open file %s\n", filename);
		return FALSE;
	}

	// TO DO: Implement this function.
	//		Don't forget to close the file
	char s[30];
	int num;
	fscanf(fp, "%s %d", s, &pt->bits_for_page_number);
	fscanf(fp, "%s %d", s, &pt->bits_for_offset);
	fscanf(fp, "%s %d", s, &pt->page_table_length);
	pt->frame_number = (int *)malloc(sizeof(int)*pt->page_table_length);
	for(int i=0;i<pt->page_table_length;i++){
		fscanf(fp, "%d", &pt->frame_number[i]);
	}
	pt->page_size = 1;
	pt->page_size = pt->page_size << pt->bits_for_offset;
	pt->limit = 1;
	pt->limit = pt->page_size * pt->page_table_length;
	fclose(fp);
	return TRUE;
}

void DisplayPageTable(PageTable *pt)
{
	printf("BITS_FOR_PAGE_NUMBER %d (maximum # of pages = %d)\n",
		pt->bits_for_page_number, 1 << pt->bits_for_page_number);
	printf("BITS_FOR_OFFSET %d (page_size = %d)\n",
		pt->bits_for_offset, pt->page_size);
	printf("PAGE_TALBLE_LENGTH %d (address limit = %d)\n", pt->page_table_length, pt->limit);

	for(int i = 0; i < pt->page_table_length; i++)
		printf("%3d: %d\n", i, pt->frame_number[i]);
}

void DestroyPageTable(PageTable *pt)
{
	// TO DO: Implement this function.
		free(pt->frame_number);
}

int Translate(int logical_addr, PageTable *pt)
{
	// TO DO: Implement this function.
	/* Hint:  use >> to retrieve page number
			  use % to retrieve page offset
			  use << and | to combine frame number and offset
	*/
	int frame = 0;
	int offset;
	int page_num = 0;
	int physical_ad;
	page_num  = logical_addr >> pt->bits_for_offset;
	offset = logical_addr %pt->page_size;
	frame = pt->frame_number[page_num] << pt->bits_for_offset;
	physical_ad = offset | frame;
	return physical_ad;

}


