#include "logger.h"

void initLogger()
{
    qDebug() <<"init logger";
    qSetMessagePattern( "[%{time MMdd h:mm:ss }] "
                       "[%{if-debug}DEBUG%{endif}"
                       "%{if-info}INFO%{endif}"
                       "%{if-warning}WARN%{endif}"
                       "%{if-critical}CRITICAL%{endif}"
                       "%{if-fatal}FATAL%{endif}] "
                       "[%{file}:%{line}] "
                       " [%{function}] "
                       "%{message}" );
}
