#include <sys/stat.h>
#include <fstream>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <iostream>
#include <assert.h>

#include "util/file.h"

namespace util {
    bool create_file(const char* file_path, u64 file_size) {
        std::ofstream fout(file_path);
        if (!fout) {
            return false;
        }
        fout.close();

        int result = truncate(file_path, file_size);
        if (result != 0) {
            return false;
        }

        std::cout << "created file \"" << file_path << "\"" << std::endl;
        return true;
    }

    void* mmap_file(const char* file_path, int& fd, u64& file_size) {
        fd = open(file_path, O_RDWR);
        struct stat sb;

        fstat(fd, &sb);
        file_size = sb.st_size;
        void* addr = mmap(0, file_size, (PROT_READ | PROT_WRITE), MAP_SHARED, fd, 0);
        return addr;
    }

    void mumap(void* addr, u64 size) {
        munmap(addr, size);
    }

    void mumap_and_close(int fd, void* addr, u64 size) {
        int res = munmap(addr, size);
        assert(res == 0);
        res = close(fd);
        assert(res == 0);
    }
} // namespace util
