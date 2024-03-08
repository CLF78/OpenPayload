#include <common/Common.hpp>
#include <egg/core/eggDecomp.hpp>
#include <game/system/DvdArchive.hpp>
#include <game/system/RaceConfig.hpp>
#include <platform/string.h>
#include <revolution/os/OSCache.h>
#include <revolutionex/net/NETDigest.h>
#include <wiimmfi/Reporting.hpp>

///////////////////////
// Wiimmfi Telemetry //
///////////////////////

// DvdArchive::decompress() override
// Hash track file, store the hash and report it to Wiimmfi if necessary
// Credits: Wiimmfi
kmBranchDefCpp(0x80519508, NULL, void, DvdArchive* self, const char* path, EGG::Heap* heap) {

    // Get decompressed size
    u32 decompressedSize = EGG::Decomp::getExpandSize(self->fileBuffer);

    // Allocate the buffer and decode the file in it
    void* buffer = heap->alloc(decompressedSize, 0x20);
    EGG::Decomp::decodeSZS(self->fileBuffer, buffer);

    // Store info and invalidate cache
    self->archiveSize = decompressedSize;
    self->archiveBuffer = buffer;
    self->archiveHeap = heap;
    DCStoreRange(buffer, decompressedSize);
    self->state = DvdArchive::DECOMPRESSED;

    // Check if it's a track file, if not bail
    if (!strstartw(path, "Race/Course/"))
        return;

    // Check if we're online, if not bail
    // We cannot use the isOnline variable since it hasn't been initialized yet
    if (!RaceConfig::instance->raceScenario.settings.isOnline())
        return;

    // We're online, send the track hash to the server
    u32 hash[5];
    NETCalcSHA1(hash, buffer, decompressedSize);
    Wiimmfi::Reporting::ReportTrackHash(hash, RaceConfig::instance->raceScenario.settings.courseId);
}
