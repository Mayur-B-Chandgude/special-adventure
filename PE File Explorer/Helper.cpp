#include "Header.h"


void CalculateOffset(int fd)
{
	IMAGE_DOS_HEADER dosheader;
	_read(fd, &dosheader, sizeof(dosheader));
	
	OffDosHeader = 0;
	OffFileHeader = dosheader.e_lfnew + 4;
	OffoptHeader = OffFileHeader + 0x14;
	OffSetHeader = OffOptHeader + sizeof(IMAGE_OPTIONAL_HEADER);
	
	_lseek(fd, 0, 0);
}


class dos_header
{
	public:
		IMAGE_DOS_HEADER dosheader;
		
		int fp;
		
		dos_header(int f)
		{
			fp = f;
			_lseek(fp, OffDosHeader.0);
			_read(f, &dosheader, sizeof(dosheader));
		}
		
		void show_header()
		{
			cout<<endl<<"-------------DOS HEADER INFO-----------------<<endl";
			cout<<"Magic Number:	"<<std::hex<<dosheader.e_magic<<endl;
			cout<<"Bytes on last page of file:	"<<dosheader.e_cblp<<endl;
			cout<<"Pages in file:	"<<dosheader.e_cp<<endl;
			cout<<"Relocation:	"<<dosheader.e_crcl<<endl;
			cout<<"Size of headers in paragraphs:	"<<dosheader.e_cparhdr<<endl;
			cout<<"Minimum extra paragraphs needed:	"<<dosheader.e_minalloc<<endl;
			cout<<"Maximum extra paragraphs needed:	"<<dosheader.e_maxalloc<<endl;
			cout<<"Initial(relative) SS value:	"<<dosheader.e_ss<<endl;
			cout<<"Initial SP value:	"<<dosheader.e_sp<<endl;
			cout<<"Checksum:	"<<dosheader.e_csum<<endl;
			cout<<"Initial IP value:	"<<doheader.e_ip<<endl;
			cout<<"Initial (relative) CS value:	"<<doheader.e_cs<<endl;
			cout<<"File adrress of relocation table:	"<<doheader.e_ifarcl<<endl;
			cout<<"Overlay Number:	"<<doheader.e_ovno<<endl;
			cout<<"OEM identifer:	"<<doheader.e_oemid<<endl;
			cout<<"OEM information(e_oemid specific):	"<<doheader.e_oeminfo<<endl;
			cout<<"RVA address of PE header:	"<<doheader.e_ifanew<<endl;
		} 
};


class file_header
{
	public:
		IMAGE_FILE_HEADER fileheader;
		
		int fp;
		
		file_header(int f)
		{
			fp = f;
			_lseek(fp, OffFileHeader, 0);
			_read(f, &fileHeader, sizeof(fileHeader));
		}
};


class opt_header
{
	public:
		IMAGE_OPTIONAL_HEADER optHeader;
		
		int fp;
		
		opt_header(int f)
		{
			fp = f;
			_lseek(fp, OffOptHeader, 0);
			_read(f, &optHeader, sizeof(optHeader));
		}
		
		void show_header()
		{
			cout<<"---------------FILE HEADER INFO-----------------"<<endl;
			cout<<"Magic:	"<<optHeader.Magic<<endl;
			cout<<"Sizze of Code:	"<<optHeader.SizeOfCode<<endl;
			cout<<"Size of Initialized Data:	"<<optHeader.SizeOfInitializedData<<endl;
			cout<<"Size of Uninitialized Data:	"<<optHeader.SizeOfUninitializedData<<endl;
			cout<<"Address of entry point:	"<<optHeader.AddressOfEntryPoint<<endl;
			cout<<"Base OF Code:	"<<optHeader.BaseOfCode<<endl;
			cout<<"Base of Data:	"<<optHeader.BaseOfData<<endl;
			cout<<"Image Base:	"<<optHeader.ImageBase<<endl;
			cout<<"Section Alignment:	"<<optHeader.SectionAlignment<<endl;
			cout<<"File Alignment:	"<<optHeader.FileAlignment<<endl;
			cout<<"Major operating System Version:	"<<optHeader.MajorOperatingSystemVersion<<endl;
			cout<<"Minor operating System Version:	"<<optHeader.MinorOperatingSystemVersion<<endl;
			cout<<"Major Image Version:	"<<optHeader.MajorImageVersion<<endl;
			cout<<"Minor Image Version:	"<<optHeader.MinorImageVersion<<endl;
			cout<<"Major subsystem Version:	"<<optHeader.MajorSubsystemVersion<<endl;
			cout<<"Minor subsystem Version:	"<<optHeader.MinorSubsystemVersion<<endl;
			cout<<"Size Of Image:	"<<optHeader.SizeOfImage<<endl;
			cout<<"Size Of Headers:	"<<optHeader.SizeOfHeader<<endl;
			cout<<"Checksum:	"<<optHeader.Checksum<<endl;
			cout<<"Sumsystem:	"<<optHeader.Subsystem<<endl;
			cout<<"Dll Characteristics:	"<<optHeader.DllCharactertics<<endl;
			cout<<"Size of stack Reverse:	"<<optHeader.SizeOfStackReverse<<endl;
			cout<<"Size of Stack Commit:	"<<optHeader.SizeOfStackCommit<<endl;
			cout<<"Size of Heap Reverse:	"<<optHeader.SizeOfHeapReverse<<endl;
			cout<<"Size of Heap Commit:	"<<optHeader.SizeOfHeapCommit<<endl;
			cout<<"Loader Flags:	"<<optHeader.LoaderFlags<<endl;
			cout<<"Number Of Rva And Sizes:	"<<optHeader.NumberOfRvaAndSizes<<endl;
		}
};


class sec_header
{
	public:
		IMAGE_SECTION_HEADER secHeader;
		
		int fp;
		int NoOfSec;
		
		sec_header(int f)
		{
			IMAGE_FILE_HEADER fileHeader;
			fp = f;
			_lseek(fp, OffFileHeader, 0);
			_read(f, &fileHeader, sizeof(fileHeader));
			NoOfSec = fileHeader.NumberOfSections;
			
			_lseek(f, OffSecHeader, 0);
			_read(f, &fileHeader, sizeof(secHeader));
		}
		
		void show_header()
		{
			cout<<endl<<"-------------SECTION HEADER INFO-------------------"<<endl;
			while(NoOfSec !=  0)
			{
				cout<<"Name:	"<<secHeader.Name<<endl;
				cout<<"Virtual Address:	"<<secHeader.VirtualAddress<<endl;
				cout<<"Size of Row Data:	"<<secHeader.SizeOfRowData<<endl;
				cout<<"Pointer To RowData:	"<<secHeader.PointerToRowData<<endl;
				cout<<"Pointer To Relocations:	"<<secHeader.PointerToRelocations<<endl;
				cout<<"Pointer To Line Numbers:	"<<secHeader.PointerToLineNumbers<<endl;
				cout<<"Number of Relocations:	"<<secHeader.NumberOfRelocations<<endl;
				cout<<"Number Of Line Numbers:	"<<secHeader.NumberOfLineNumbers<<endl;
				
				NoOfSec--;
				
				cout<<endl<<"----------------------------------------<<endl";
				
				_read(fp, &secHeader, sizeof(secHeader));
			}
		}
}

