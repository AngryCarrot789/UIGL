//
// Created by kettl on 04/01/2023.
//

#ifndef UIGL_DISPATCHERGLOBALS_H
#define UIGL_DISPATCHERGLOBALS_H

enum DispatcherPriority {
    APP_PRE_TICK,
    INPUT_PRE,
    INPUT_POST,
    RENDER_PRE,
    RENDER_POST,
    APPLICATION_IDLE,
    CONTEXT_IDLE,
    APP_POST_TICK
};

typedef void (* Action /* typedef name */ )( /* params */ );

#endif //UIGL_DISPATCHERGLOBALS_H
