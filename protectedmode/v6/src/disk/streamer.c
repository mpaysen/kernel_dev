#include "streamer.h"
#include "memory/heap/kheap.h"
#include "config.h"

struct disk_stream* disk_stream_new(int disk_id){
    struct disk* disk = disk_get(disk_id);
    if (!disk){ //if disk is invalid return 0
        return 0;
    }

    struct disk_stream* streamer = kzalloc(sizeof(struct disk_stream));
    streamer->pos = 0;
    streamer->disk = disk;
    return streamer;
}

int diskstreamer_seek(struct disk_stream* stream, int pos){
    stream->pos = pos; //update pos
    return 0;
}

int diskstreamer_read(struct disk_stream* stream, void* out, int total){ //read from the disk stream total amount of bytes
    int sector = stream->pos / M_OS_SECTOR_SIZE;
    int offset = stream->pos % M_OS_SECTOR_SIZE;
    char buf[M_OS_SECTOR_SIZE]; //read to the Stack (one Sector)

    int res = disk_read_block(stream->disk, sector, 1, buf);
    if (res < 0) {
        goto out;
    }

    int total_to_read = total > M_OS_SECTOR_SIZE ? M_OS_SECTOR_SIZE : total; //max. one Sector
    for (int i = 0; i < total_to_read; i++) {
        *(char*)out++ = buf[offset + i]; //read from the Stack to out.
    }


    // Adjust the stream
    stream-> pos += total_to_read; //outpointer is now 512 bytes ahead
    if (total > M_OS_SECTOR_SIZE) {
        res = diskstreamer_read(stream, out, total - M_OS_SECTOR_SIZE); // using recrusion to read the reamining bytes, is possebile to overflow the Stack, because of recursion
    }


out:
    return res;
}

void diskstreamer_close(struct disk_stream* stream){
    kfree(stream);
}
