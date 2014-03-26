#include "voreenapplicationqt5.h"

using std::string;

namespace voreen {

VoreenApplicationQt5* VoreenApplicationQt5::qtApp_ = 0;
const std::string VoreenApplicationQt5::loggerCat_ = "voreenqt.VoreenApplicationQt5";

VoreenApplicationQt5::VoreenApplicationQt5(const std::string& name, const std::string& displayName, const std::string& description,
                                         int argc, char** argv, ApplicationFeatures appType)
    : VoreenApplication(name, displayName, description, argc, argv, appType)
    , resetApplicationSettingsButton_("resetApplicationSettings", "Reset Window Settings")
    , scaleProcessorFontSizeProperty_("scaleProcessorFontSize","Scale Processor Fonts:",100,50,150)
    , mainWindow_(0)
    , clearSettings_(false)
{
    qApp->setOrganizationName("Voreen");
    qApp->setOrganizationDomain("voreen.org");
    qApp->setApplicationName(displayName.c_str());

    addProperty(resetApplicationSettingsButton_);
    resetApplicationSettingsButton_.setGroupID("user-interface");
    //network editor properties
    addProperty(scaleProcessorFontSizeProperty_);
        scaleProcessorFontSizeProperty_.setGroupID("nwe");
    setPropertyGroupGuiName("nwe","Network Editor");

    qtApp_ = this;
}

VoreenApplicationQt5::~VoreenApplicationQt5() {

}

void VoreenApplicationQt5::initialize() throw (VoreenException) {
    VoreenApplication::initialize();
}

void VoreenApplicationQt5::deinitialize() throw (VoreenException) {
    VoreenApplication::deinitialize();
}

void VoreenApplicationQt5::initializeGL() throw (VoreenException) {
    VoreenApplication::initializeGL();
}

void VoreenApplicationQt5::deinitializeGL() throw (VoreenException) {
    VoreenApplication::deinitializeGL();
}

void VoreenApplicationQt5::setMainWindow(QWindow* mainWindow) {
    mainWindow_ = mainWindow;
}

QWindow* VoreenApplicationQt5::getMainWindow() const {
    return mainWindow_;
}

VoreenApplicationQt5* VoreenApplicationQt5::qtApp() {
    return qtApp_;
}

tgt::Timer* VoreenApplicationQt5::createTimer(tgt::EventHandler* handler) const {
    return new tgt::QtTimer(handler);
}

void VoreenApplicationQt5::resetApplicationSettings() {
    QSettings settings;
    settings.clear();
    clearSettings_ = true;
}

int VoreenApplicationQt5::getProcessorFontScale() const {
    return scaleProcessorFontSizeProperty_.get();
}

} // namespace

