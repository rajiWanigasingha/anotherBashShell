//
// Created by rajindawanigasingha on 5/10/26.
//

#ifndef ANOTHERBASHSHELL_FILE_ATTRIBUTES_H
#define ANOTHERBASHSHELL_FILE_ATTRIBUTES_H
#include <signal.h>
#include <time.h>
#include <sys/types.h>

/**
 * @brief Enumeration of file types returned by stat system call.
 *
 * @details
 * Represents the different file types that can be determined from
 * file status information. These types correspond to the file type
 * bits in the st_mode field of struct stat.
 *
 * - `FILETYPE_REG_FILE`: Regular file
 * - `FILETYPE_DIRECTORY`: Directory
 * - `FILETYPE_SYMLINK`: Symbolic link
 * - `FILETYPE_SOCKET`: Socket
 * - `FILETYPE_FIFO`: FIFO (named pipe)
 */
enum FileTypeInStat {
    FILETYPE_REG_FILE,
    FILETYPE_DIR,
    FILETYPE_SYMLINK,
    FILETYPE_SOCKET,
    FILETYPE_FIFO,
};

typedef enum FileTypeInStat FileTypeInStat;

/**
 * @brief Represents permission bits for read, write, and execute operations.
 *
 * @details
 * Stores the permission bit flags extracted from the st_mode field of
 * struct stat. Each field contains a bitmask value that indicates whether
 * the corresponding permission is set (non-zero) or not set (zero).
 *
 * The values are obtained by bitwise AND operations with permission constants
 * (e.g., S_IRUSR, S_IWUSR, S_IXUSR for owner permissions).
 *
 * - `read`: Read permission bit (e.g., S_IRUSR & st_mode)
 * - `write`: Write permission bit (e.g., S_IWUSR & st_mode)
 * - `execute`: Execute permission bit (e.g., S_IXUSR & st_mode)
 */
struct PermissionBits {
    mode_t read;
    mode_t write;
    mode_t execute;
};

typedef struct PermissionBits PermissionBits;

/**
 * @brief Represents file permissions for owner, group, and others.
 *
 * @details
 * Stores the permission information for a file or directory, organized
 * by ownership class. Each field contains a PermissionBits structure
 * that holds the read, write, and execute permission bits.
 *
 * The permissions correspond to the traditional Unix permission model:
 * - `owner`: Permissions for the file owner (user)
 * - `group`: Permissions for the group owner
 * - `others`: Permissions for all other users
 *
 * These values are typically extracted from the st_mode field of
 * struct stat using bitwise operations with permission constants
 * (S_IRUSR, S_IWUSR, S_IXUSR, S_IRGRP, S_IWGRP, S_IXGRP, S_IROTH, S_IWOTH, S_IXOTH).
 */
struct FilePermissions {
    PermissionBits owner;
    PermissionBits group;
    PermissionBits others;
};

typedef struct FilePermissions FilePermissions;

/**
 * @brief Represents file timestamp information.
 *
 * @details
 * Stores the three main timestamps associated with a file or directory,
 * as provided by the stat system call. Each timestamp is represented
 * as a pointer to a struct tm, which contains broken-down time information.
 *
 * The timestamps correspond to:
 * - `last_access`: Time of last access (st_atime from struct stat)
 * - `last_modified`: Time of last modification (st_mtime from struct stat)
 * - `last_change`: Time of last status change (st_ctime from struct stat)
 *
 * Note: These pointers reference the result of gmtime() or localtime(),
 * which return static data that may be overwritten by subsequent calls.
 */
struct FileTime {
    struct tm* last_access;
    struct tm* last_modified;
    struct tm* last_change;
};

typedef struct FileTime FileTime;

/**
 * @brief Represents file owner and group identifiers.
 *
 * @details
 * Stores the user ID (UID) and group ID (GID) associated with a file
 * or directory. These values are obtained from the st_uid and st_gid
 * fields of struct stat returned by the stat system call.
 *
 * - `owner`: User ID (UID) of the file owner
 * - `group`: Group ID (GID) of the file's group owner
 */
struct FileOwnerId {
    uid_t owner;
    gid_t group;
};

typedef struct FileOwnerId FileOwnerId;

/**
 * @brief Represents comprehensive file attributes retrieved from the filesystem.
 *
 * @details
 * This structure aggregates all the key attributes of a file or directory
 * obtained through the stat system call. It provides a comprehensive view
 * of file metadata including type, permissions, size, timestamps, and ownership.
 *
 * This struct is typically populated by the file_attributes() function and
 * returned within an Attributes wrapper structure.
 *
 * Fields:
 * - `type`: The type of the file (regular, directory, symlink, socket, FIFO)
 * - `permissions`: Complete permission information for owner, group, and others
 * - `size`: Size of the file in bytes (from st_size field of struct stat)
 * - `time`: Timestamp information (last access, modification, and status change)
 * - `owner`: User and group ownership identifiers (UID and GID)
 *
 * @note The time field contains pointers to static data from gmtime() which may
 *       be overwritten by subsequent calls.
 *
 * @see Attributes
 * @see file_attributes()
 */
struct FileAttributes {
    FileTypeInStat type;
    FilePermissions permissions;
    size_t size;
    FileTime time;
    FileOwnerId owner;
};

typedef struct FileAttributes FileAttributes;

/**
 * @brief Wrapper structure for file attribute retrieval results.
 *
 * @details
 * This structure provides a result type pattern for the file_attributes() function,
 * indicating success or failure and containing either the requested file attributes
 * or an error message.
 *
 * Fields:
 * - `is_ok`: Success flag (1 = success, 0 = failure)
 * - `error`: Error message string on failure, NULL on success
 * - `attributes`: File attribute data on success
 *
 * @see file_attributes()
 * @see FileAttributes
 */
struct Attributes {
    size_t is_ok;
    char* error;
    FileAttributes attributes;
};

typedef struct Attributes Attributes;

/**
 * @brief Retrieves comprehensive file attributes for a given file path.
 *
 * @details
 * This function queries the filesystem for detailed information about a file
 * or directory using the stat system call. It collects and organizes various
 * file metadata including type, permissions, size, timestamps, and ownership
 * information into a structured format.
 *
 * The function performs the following operations:
 * - Calls stat() to retrieve raw file status information
 * - Determines the file type (regular file, directory, symlink, socket, or FIFO)
 * - Extracts and organizes permission bits for owner, group, and others
 * - Retrieves file size in bytes
 * - Converts timestamps to broken-down time structures
 * - Extracts user and group ownership identifiers
 *
 * @param file_name Path to the file or directory (absolute or relative)
 *
 * @return Attributes structure containing:
 *         - On success (is_ok = 1): populated FileAttributes with all file metadata
 *         - On failure (is_ok = 0): error message describing the failure reason
 *
 * @see Attributes
 * @see FileAttributes
 * @see stat(2)
 */
Attributes file_attributes(const char* file_name);

#endif //ANOTHERBASHSHELL_FILE_ATTRIBUTES_H