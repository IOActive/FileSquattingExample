#pragma once
#include "stdafx.h"
#include <Windows.h>
#include <winternl.h>

void create_dos_device_symlink(WCHAR *src, WCHAR *dst);
void remove_dos_device_symlink(WCHAR *src, WCHAR *dst);

BOOL create_mount_point(WCHAR *srcDirectory, WCHAR *dstDirectory);
BOOL create_mount_point_with_handle(HANDLE hSrcDirectory, WCHAR *dstDirectory);
BOOL delete_mount_point(WCHAR *path);
BOOL is_mounted_directory(WCHAR *directoryName);
HANDLE open_file_handle(WCHAR *filename, DWORD dwSharedMode);


typedef void(*UserCallback)();

typedef struct _FILE_OPLOCK {
	HANDLE hFile;
	OVERLAPPED overlapped;
	REQUEST_OPLOCK_INPUT_BUFFER InputBuffer;
	REQUEST_OPLOCK_OUTPUT_BUFFER OutputBuffer;
	HANDLE g_hLockCompleted;
	PTP_WAIT ptpWait;
	UserCallback Callback;
	WCHAR fileName[1024];
} FILE_OPLOCK;


FILE_OPLOCK* create_oplock(WCHAR *filename, DWORD shareMode, UserCallback opLockCallback);
void wait_for_lock(FILE_OPLOCK *opLock, UINT Timeout);
void delete_oplock(FILE_OPLOCK *opLock);

void create_pseudo_symlink(WCHAR *src, WCHAR *dst);
void delete_pseudo_symlink(WCHAR *src, WCHAR *dst);



typedef NTSTATUS(__stdcall *_ZwSetInformationFile)(
	_In_   HANDLE                 FileHandle,
	_Out_  PIO_STATUS_BLOCK       IoStatusBlock,
	_In_   PVOID                  FileInformation,
	_In_   ULONG                  Length,
	_In_   ULONG			      FileInformationClass
	);

typedef NTSTATUS(NTAPI* _NtOpenFile)(
	_Out_ PHANDLE            FileHandle,
	_In_  ACCESS_MASK        DesiredAccess,
	_In_  POBJECT_ATTRIBUTES ObjectAttributes,
	_Out_ PIO_STATUS_BLOCK   IoStatusBlock,
	_In_  ULONG              ShareAccess,
	_In_  ULONG              OpenOptions
	);

typedef void (NTAPI *_RtlInitUnicodeString)(
	PUNICODE_STRING DestinationString,
	PCWSTR SourceString
	);

_ZwSetInformationFile fpZwSetInformationFile;
_NtOpenFile fpNtOpenFile;
_RtlInitUnicodeString fpRtlInitUnicodeString;


BOOL create_hardlink(WCHAR *srcNativeFile, WCHAR *targetFile);

// Util
WCHAR **parse_arguments(WCHAR *command_line, WCHAR arg_delim);
void get_user_input(WCHAR *input, int size);
void print_memory(unsigned long address, char *buffer, unsigned int bytes_to_print);
void error(WCHAR *msg);
