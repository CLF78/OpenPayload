#include <common/Common.hpp>
#include <revolution/mtx.h>

struct KmpSectionHeader {
    s32 sectionMagic;
    u16 entryCount;
    s8 extraValue[2];
};

template <typename T>
class MapdataAccessorBase {
public:
    T** entries;
    u16 numEntries;
    KmpSectionHeader* sectionHeader;
};

class MapdataPointInfo {
public:

    struct SData {
        struct Point {
            VEC3 pos;
            u16 settings[2];
        };

        u16 pointCount;
        u8 settings[2];
        Point points[];
    };

    SData* mpData;
};

class MapdataCamera {
public:

    struct SData {
        u8 cameraType;
        u8 cameraNext;
        u8 cameraShake;
        u8 pathID;
        u16 pathSpeed;
        u16 fovYSpeed;
        u16 viewSpeed;
        u8 startFlag;
        u8 movieFlag;
        VEC3 position;
        VEC3 rotation;
        f32 fovYStart;
        f32 fovVYEnd;

        VEC3 viewStart;
        VEC3 viewEnd;

        f32 time;
    };

    SData* mpData;
};

class MapdataCannonPoint {
public:

    struct SData {
        VEC3 position;
        VEC3 rotation;
        u16 id;
        u16 shootEffect;
    };

    SData* mpData;
};

class MapdataCheckPath {
public:

    struct SData {
        u8 start;
        u8 size;

        u8 last[6];
        u8 next[6];
    };

    SData* mpData;

    u8 dfsDepth;
    float _8;
};

class MapdataCheckPoint {
public:
    struct SData {
        VEC2 left;
        VEC2 right;
        u8 jugemIndex;
        u8 lapCheck;
        u8 prevPt;
        u8 nextPt;
    };

    struct Link {
        MapdataCheckPoint* checkpoint;
        VEC2 p0diff;
        VEC2 p1diff;
        float distance;
    };

    SData* mpData;

    u16 nextCount;
    u16 prevCount;

    VEC2 midPoint;
    VEC2 dir;

    u16 _18;
    u16 id;

    u8 prevKcpId;
    MapdataCheckPoint* prevCheckPoints[6];
    Link nextCheckPoints[6];
};

class MapdataEnemyPath {
public:

    struct SData {
        u8 start;
        u8 size;
        u8 last[6];
        u8 next[6];
        u8 battle_params[2];
    };

    SData* mpData;
    u8 _4[0x0C - 0x04];
};

class MapdataEnemyPoint {
public:

    struct SData {
        VEC3 position;
        f32 deviation;
        u8 parameters[4];
    };

    virtual ~MapdataEnemyPoint();
    SData* mpData;

    u32* _8;
    u32* _c;
    u32 _10;
    u8 _14;
};

class MapdataGeoObj {
public:

    struct SData {
        u16 id;
        VEC3 translation;
        VEC3 rotation;
        VEC3 scale;
        s16 pathId;
        u16 settings[8];
        u16 presenceFlag;
    };

    SData* mpData;
};

class MapdataItemPath {
public:

    struct SData {
        u8 start;
        u8 size;

        u8 last[6];
        u8 next[6];

        u16 _E; // Required padding
    };

    SData* mpData;
};

class MapdataItemPoint {
public:

    struct SData {
        VEC3 position;
        f32 deviation;
        u16 parameters[2];
    };

    SData* mpData;
    u8 _4[0x14 - 0x04];
};

class MapdataJugemPoint {
public:

    struct SData {
        VEC3 position;
        VEC3 rotation;
        u16 id;
        s16 range;
    };

    SData* mpData;

    VEC3 _4;
    VEC3 _8;
    VEC3 _C;

    u8 enemyPoint;
    u8 itemPoint;

    u16 _2A;
    u16 _2C;
};

class MapdataMissionPoint {
public:

    struct SData {
        VEC3 position;
        VEC3 rotation;
        u16 id;
    };

    SData* mpData;
};

class MapdataStage {
public:

    struct SData {
        u8 mLapCount;
        bool mPolePosition;
        bool mStartConfig;
        bool mFlareToggle;
        u32 mFlareColor;
        u8 mFlareAlpha;
        u8 _9;
        u16 mSpeedMod; // custom
    };

    SData* mpData;
};

class MapdataStartPoint {
public:

    struct SData {
        VEC3 position;
        VEC3 rotation;
        s16 playerIndex;
    };

    SData* mpData;
    s8 mEnemyPoint;
};

class MapdataAreaBase {
public:

    enum Type {
        CAMERA_LINK,
        ENV_EFFECT,
        FOG_SWAP,
        MOVING_ROAD,
        RECALC_DEST,
        MINIMAP_CONTROL,
        BLOOM_SWAP,
        FLYING_BOOS,
        OBJECT_GROUP,
        OBJECT_GROUP_UNLOAD,
        FALL_BOUNDARY,
    };

    struct SData {
        u8 shape;
        u8 type;
        s8 cameraIdx;
        u8 priority;
        VEC3 position;
        VEC3 rotation;
        VEC3 scale;
        u16 parameters[2];
        u8 railID;
        u8 eneLinkID;
    };

    virtual bool isInsideShape(const VEC3& pos) const = 0;

    SData* mpData;
    VEC3 mXAxis;
    VEC3 mYAxis;
    VEC3 mZAxis;
    VEC3 mDims;

    f32 mEllipseXRadiusSq;
    f32 mEllipseAspectRatio;
    f32 mBoundingSphereRadiusSq;

    s16 mIndex;
};

class MapdataAreaBox : public MapdataAreaBase {
public:
    virtual bool isInsideShape(const VEC3& pos) const;
};

class MapdataAreaCylinder : public MapdataAreaBase {
public:
    virtual bool isInsideShape(const VEC3& pos) const;
};

class MapdataAreaAccessor {
public:
    MapdataAreaBase** entries;
    u16 numEntries;

    virtual ~MapdataAreaAccessor();

    KmpSectionHeader* sectionHeader;
    MapdataAreaBase** byPriority;
};

class MapdataCameraAccessor : public MapdataAccessorBase<MapdataCamera> {
};

class MapdataCannonPointAccessor : public MapdataAccessorBase<MapdataCannonPoint> {
};

class MapdataCheckPathAccessor : public MapdataAccessorBase<MapdataCheckPath> {
public:
    f32 _C;
};

class MapdataCheckPointAccessor : public MapdataAccessorBase<MapdataCheckPoint> {
public:
    s8 lastKcpId;
    u16 finishLineId;
    float meanTotalDistance;
};

class MapdataEnemyPathAccessor : public MapdataAccessorBase<MapdataEnemyPath> {
};

class MapdataEnemyPointAccessor : public MapdataAccessorBase<MapdataEnemyPoint> {
};

class MapdataGeoObjAccessor : public MapdataAccessorBase<MapdataGeoObj> {
};

class MapdataItemPathAccessor : public MapdataAccessorBase<MapdataItemPath> {
};

class MapdataItemPointAccessor : public MapdataAccessorBase<MapdataItemPoint> {
};

class MapdataJugemPointAccessor : public MapdataAccessorBase<MapdataJugemPoint> {
};

class MapdataMissionPointAccessor : public MapdataAccessorBase<MapdataMissionPoint> {
};

class MapdataPointInfoAccessor : public MapdataAccessorBase<MapdataPointInfo> {
};

class MapdataStageAccessor : public MapdataAccessorBase<MapdataStage> {
};

class MapdataStartPointAccessor : public MapdataAccessorBase<MapdataStartPoint> {
};

class MapdataFileAccessor {
public:

    struct SData {
        u32 magic;
        u32 fileSize;
        u16 numSections;
        u16 headerSize;
        u32 revision;
        s32 offsets[];
    };

    SData* mpData;
    u32* mpSectionDef;
    u32 mVersion;
    u32 mSectionDefOffset;
};

class CourseMap {
public:
    virtual ~CourseMap();
    void init();

    s16 getClosestAreaIdByType(VEC3* pos, s16 prevAreaId, s16 type); // prevAreaId = previous area this function returned

    MapdataFileAccessor* mpCourse;

    MapdataStartPointAccessor* mpStartPoint;
    MapdataEnemyPathAccessor* mpEnemyPath;
    MapdataEnemyPointAccessor* mpEnemyPoint;
    MapdataItemPathAccessor* mpItemPath;
    MapdataItemPointAccessor* mpItemPoint;
    MapdataCheckPathAccessor* mpCheckPath;
    MapdataCheckPointAccessor* mpCheckPoint;
    MapdataPointInfoAccessor* mpPointInfo;
    MapdataGeoObjAccessor* mpGeoObj;
    MapdataAreaAccessor* mpArea;
    MapdataCameraAccessor* mpCamera;
    MapdataJugemPointAccessor* mpJugemPoint;
    MapdataCannonPointAccessor* mpCannonPoint;
    MapdataStageAccessor* mpStageInfo;
    MapdataMissionPointAccessor* mpMissionPoint;

    MapdataCamera* mpGoalCamera;
    MapdataCamera* mpMissionGoalCamera;
    MapdataCamera* mpOpeningCamera;
    u32 _50;

    static CourseMap* instance;
};
