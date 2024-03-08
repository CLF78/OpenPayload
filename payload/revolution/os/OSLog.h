#ifdef __cplusplus
extern "C" {
#endif

void OSReport(const char* format, ...);
#define DEBUG_REPORT(...) if (DEBUG) { OSReport(__VA_ARGS__); }

#ifdef __cplusplus
}
#endif
