#include "AppDelegate.h"
#include "Scenes/MainMenu.h"

USING_NS_CC;

AppDelegate::AppDelegate()
{
}

AppDelegate::~AppDelegate() 
{
    FileUtils::getInstance()->destroyInstance();
    SpriteFrameCache::getInstance()->destroyInstance();
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLView::create("Gem Crasher");
        director->setOpenGLView(glview);
    }

#if (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX) || (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
    glview->setFrameSize(375, 600);
#endif
    glview->setDesignResolutionSize(375, 600, ResolutionPolicy::FIXED_HEIGHT);

    //auto winSize = director->getWinSize();
    std::vector<std::string> resOrder;

    resOrder.push_back("HD");

    FileUtils::getInstance()->setSearchResolutionsOrder(resOrder);
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("ss.plist", "ss.png");

    //director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

    // run
    director->runWithScene(MainMenu::create());

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
