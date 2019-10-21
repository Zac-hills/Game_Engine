#ifndef __LIB_SETTINGS_H__
#define __LIB_SETTINGS_H__

#ifdef  ENTITY_COMPONENT_SYSTEM
# define LIB_API __declspec(dllexport)
#elif   ENTITY_COMPONENT_SYSTEM
# define LIB_API __declspec(dllimport)
#else
# define LIB_API
#endif



#endif