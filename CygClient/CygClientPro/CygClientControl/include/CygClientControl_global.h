#ifndef CYG_CLIENTCONTROL_GLOBAL_H
#define CYG_CLIENTCONTROL_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(CYG_CLIENTCONTROL_LIBRARY)
#define CYG_CLIENTCONTROL_EXPORT Q_DECL_EXPORT
#else
#define CYG_CLIENTCONTROL_EXPORT Q_DECL_IMPORT
#endif

#endif // CYG_CLIENTCONTROL_GLOBAL_H 