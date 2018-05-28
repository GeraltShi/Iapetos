#ifndef  _APP_DELEGATE_H_
#define  _APP_DELEGATE_H_

#include "cocos2d.h"
USING_NS_CC;

class  AppDelegate : Application
{
public:
    AppDelegate();
    virtual ~AppDelegate();

    void initGLContextAttrs() override;
    bool applicationDidFinishLaunching() override;
    void applicationDidEnterBackground() override;
    void applicationWillEnterForeground() override;
};

#endif // _APP_DELEGATE_H_

