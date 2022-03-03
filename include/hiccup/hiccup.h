#ifndef __HICCPU_H__
#define __HICCPU_H__

#define HICCUP_NS hiccpu
#define HICCUP_BEGIN namespace HICCUP_NS {
#define HICCUP_END }
#define USING_HICCUP using namespace HICCUP_NS;
#define DECL_HICCUP_OF(type) namespace HICCUP_NS { struct type; }

#endif