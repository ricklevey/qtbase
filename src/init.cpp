#include "wrappers.h"
#include "utils.hpp"
#include "Reference.hpp"

#include <Rinternals.h>
#include <R_ext/Rdynload.h>
#include <R_ext/Print.h>


extern "C" {
  
    // Test.cpp
    SEXP newLabelWidget(SEXP label);

    // style.cpp

    SEXP qt_qsetStyleSheet(SEXP x, SEXP s);
    SEXP qt_qstyleSheet(SEXP x);

    // actions.cpp

    SEXP qt_qaction(SEXP desc, SEXP shortcut, SEXP parent, SEXP tooltip,
                    SEXP checkable);
    SEXP qt_qaddActionToQWidget(SEXP w, SEXP a);
    SEXP qt_qaddAction_QGraphicsWidget(SEXP w, SEXP a);
    SEXP qt_qaddActionToQMenu(SEXP w, SEXP a);
    SEXP qt_qsetContextMenuPolicy(SEXP x, SEXP policy);

    // attributes.cpp

    SEXP qt_qsetDeleteOnClose(SEXP x, SEXP status);

    // this file 

    SEXP addQtEventHandler();
    SEXP cleanupQtApp();

    void R_init_qtbase(DllInfo *dll);

    extern void init_utils();

  // signals
  SEXP qt_qconnect(SEXP x, SEXP user_data, SEXP handler, SEXP which);
  SEXP qt_qdisconnect(SEXP x, SEXP receiver);

  // metadata
  SEXP qt_qnormalizedSignature(SEXP x);
  SEXP qt_qmethods(SEXP rself);
  SEXP qt_qproperties(SEXP x);

  // dynamic invocation
  SEXP qt_qinvoke(SEXP rmethod, SEXP robj, SEXP rargs);

  // properties
  SEXP qt_qsetProperty(SEXP x, SEXP rname, SEXP rvalue);
  SEXP qt_qproperty(SEXP x, SEXP name);
}

QObject* unwrapQObjectReferee(SEXP x);

#define CALLDEF(name, n)  {#name, (DL_FUNC) &name, n}

static R_CallMethodDef CallEntries[] = {



    CALLDEF(qt_qsetStyleSheet, 2),
    CALLDEF(qt_qstyleSheet, 1),

    CALLDEF(addQtEventHandler, 0),
    CALLDEF(cleanupQtApp, 0),

    CALLDEF(newLabelWidget, 1),

    CALLDEF(qt_qaction, 5),
    CALLDEF(qt_qaddActionToQWidget, 2),
    CALLDEF(qt_qaddActionToQMenu, 2),
    CALLDEF(qt_qaddAction_QGraphicsWidget, 2),
    CALLDEF(qt_qsetContextMenuPolicy, 2),

    CALLDEF(qt_qsetDeleteOnClose, 2),

    CALLDEF(qt_qdisconnect, 2),
    CALLDEF(qt_qconnect, 5),

    CALLDEF(qt_qnormalizedSignature, 1),
    CALLDEF(qt_qmethods, 1),
    CALLDEF(qt_qproperties, 1),

    CALLDEF(qt_qinvoke, 3),

    CALLDEF(qt_qsetProperty, 3),
    CALLDEF(qt_qproperty, 2),
    
    {NULL, NULL, 0}
};


#define REG_CALLABLE(fun) R_RegisterCCallable("qtbase", #fun, (DL_FUNC) fun)

void R_init_qtbase(DllInfo *dll)
{
    init_utils(); // initializes some things unrelated to event handling

    // Register C routines
    R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);

    // Register for calling by other packages.
    REG_CALLABLE(wrapQWidget);
    REG_CALLABLE(wrapQObject);
    REG_CALLABLE(wrapPointer);
    REG_CALLABLE(unwrapQObjectReferee);
    REG_CALLABLE(wrapQGraphicsWidget);
    REG_CALLABLE(wrapQGraphicsItem);
    
    REG_CALLABLE(asStringArray);
    REG_CALLABLE(sexp2qstring);
    REG_CALLABLE(asRStringArray);
    REG_CALLABLE(qstring2sexp);
    
    REG_CALLABLE(addQObjectReference);
    REG_CALLABLE(addQWidgetReference);
    REG_CALLABLE(addQGraphicsWidgetReference);
    REG_CALLABLE(addQGraphicsItemReference);
}
