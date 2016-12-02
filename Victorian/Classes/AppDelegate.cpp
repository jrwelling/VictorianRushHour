#include "AppDelegate.h"
#include "SimpleAudioEngine.h"
#include "HelloWorldScene.h"

USING_NS_CC;

using namespace CocosDenshion;

static cocos2d::Size designResolutionSize = cocos2d::Size(480, 320);
static cocos2d::Size smallResolutionSize = cocos2d::Size(480, 320);
static cocos2d::Size mediumResolutionSize = cocos2d::Size(1024, 768);
static cocos2d::Size largeResolutionSize = cocos2d::Size(2048, 1536);

AppDelegate::AppDelegate()
{
}

AppDelegate::~AppDelegate() 
{
}

// if you want a different context, modify the value of glContextAttrs
// it will affect all platforms
void AppDelegate::initGLContextAttrs()
{
    // set OpenGL context attributes: red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

// if you want to use the package manager to install more packages,  
// don't modify or remove this function
static int register_all_packages()
{
    return 0; //flag for packages manager
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLViewImpl::create("Victorian Game");
        director->setOpenGLView(glview);
    }
    
    // turn on display FPS
    director->setDisplayStats(true);
    
    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);
    
    Size screenSize = glview->getFrameSize();
    Size designSize = Size(2048, 1536);
    
    glview->setDesignResolutionSize(designSize.width, designSize.height, ResolutionPolicy::EXACT_FIT);
    
    std::vector<std::string> searchPaths;
    
    if (screenSize.height > 768) {
        searchPaths.push_back("ipadhd");
        director->setContentScaleFactor(1536/designSize.height);
    } else if (screenSize.height > 320) {
        searchPaths.push_back("ipad");
        director->setContentScaleFactor(768/designSize.height);
    } else {
        searchPaths.push_back("iphone");
        director->setContentScaleFactor(380/designSize.height);
    }
    
    auto fileUtils = FileUtils::getInstance();
    fileUtils->setSearchPaths(searchPaths);
    
    auto audioEngine = SimpleAudioEngine::getInstance();
    
    audioEngine->preloadBackgroundMusic(fileUtils->fullPathForFilename("background3.mp3").c_str());
    audioEngine->preloadEffect( fileUtils->fullPathForFilename("falling.wav").c_str() );
    audioEngine->preloadEffect( fileUtils->fullPathForFilename("hitBuilding.wav").c_str() );
    audioEngine->preloadEffect( fileUtils->fullPathForFilename("jump.wav").c_str() );
    audioEngine->preloadEffect( fileUtils->fullPathForFilename("crashing.wav").c_str() );
    audioEngine->preloadEffect( fileUtils->fullPathForFilename("start.wav").c_str() );
    audioEngine->preloadEffect( fileUtils->fullPathForFilename("openUmbrella.wav").c_str() );
    
    audioEngine->setBackgroundMusicVolume(0.5f);
    audioEngine->setEffectsVolume(0.5f);
    
    
    // create a scene. it's an autorelease object
    auto scene = HelloWorld::createScene();
    
    // run
    director->runWithScene(scene);
    
    return true;
}

// This function will be called when the app is inactive. Note, when receiving a phone call it is invoked.
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be paused
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
