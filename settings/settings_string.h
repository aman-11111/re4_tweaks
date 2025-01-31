#pragma once
const char* defaultSettings = R""""(
[DISPLAY]
; Additional FOV value. 20 seems good for most cases.
FOVAdditional = 0.0

; Force V-Sync to be disabled. For some reason the vanilla game doesn't provide a functional way to do this.
DisableVsync = false

; Fixes the incorrect aspect ratio when playing in ultrawide resolutions, 
; preventing the image from being cut off and the HUD appearing off-screen.
UltraWideAspectSupport = true

; Moves the HUD to the right side of the screen when when playing in ultrawide.
SideAlignHUD = true

; Streches some images to fit the screen, such as the images shown when reading "Files".
; Only relevant if playing in ultrawide or if Remove16by10BlackBars is enabled.
StretchFullscreenImages = false

; Streches pre-rendered videos to fit the screen.
; Only relevant if playing in ultrawide or if Remove16by10BlackBars is enabled.
StretchVideos = false

; Removes top and bottom black bars that are present when playing in 16:10.
; Will crop a few pixels from each side of the screen.
Remove16by10BlackBars = true

; Replaces the games 60/30FPS framelimiter with our own version, which reduces CPU usage quite a lot.
; (experimental, not known if the new framelimiter performs the same as the old one yet)
ReplaceFramelimiter = true

; Forces game to run at normal 100% DPI scaling, fixes resolution issues for players that have above 100% DPI scaling set.
FixDPIScale = true

; Allows the game to use non-60Hz refresh rates in fullscreen, fixing the black screen issue people have
; when starting it.
FixDisplayMode = true

; Determines a custom refresh rate for the game to use.
; Requires FixDisplayMode to be enabled.
; -1 will make it try to use the current refresh rate as reported by Windows.
CustomRefreshRate = -1

; Overrides the color of the laser sights.
; Values used here are RGB, in that order.
; Note: The game's vanilla config.ini contains a setting to change the alpha/opacity of the laser,
; but since it doesn't work, we don't include it here.
OverrideLaserColor = false
RainbowLaser = false
LaserR = 255
LaserG = 0
LaserB = 0

; Restores a transparency effect that is missing from the item pickup screeen.
RestorePickupTransparency = true

; This filter was originally meant to add an extra glow effect on certain fire sources, but it was broken
; when the game was ported to the Xbox 360, making the entire image have an orange tint overlay applied to it.
; (if you're using the HD Project, you should disable this option)
DisableBrokenFilter03 = true

; Fixes a problem related to a vertex buffer that caused the image to be slightly blurred,
; making the image much sharper and clearer.
FixBlurryImage = true

; Disables the film grain overlay that is present in most sections of the game.
DisableFilmGrain = true

; Restores DoF blurring from the GC version, which was removed/unimplemented in later ports.
EnableGCBlur = true

; Choose GC blur type.
; Enhanced = Slightly improved implementation to look better on modern high-definition displays.
; Classic = The original GC implementation.
GCBlurType = Enhanced

; Restores outer-scope blurring when using a scope, which was removed/unimplemented in later ports.
EnableGCScopeBlur = true

; Whether to use a borderless-window when using windowed-mode.
WindowBorderless = false

; Position to draw the game window when using windowed mode.
; -1 will use the games default (usually places it at 0,0)
WindowPositionX = -1
WindowPositionY = -1

; Remember the last window position. This automatically updates the "WindowPositionX" and "WindowPositionY" values.
RememberWindowPos = false

[AUDIO]
; Allows seperate adjustment of background music/sound effect/cutscene volume
; VolumeCutscene will also affect volume of merchant screen dialogue, as that seems to be handled the same way as cutscenes.
; Min 0, max 100.
VolumeMaster = 100
VolumeBGM = 100
VolumeSE = 100
VolumeCutscene = 100

[MOUSE]
; Provides a small set of camera tweaks:
; - Aim weapons in the direction the camera is pointing to;
; - Stop camera from being randomly reset;
; - Allow full 360 degree movement;
; - Smoother and more responsive movement;
CameraImprovements = true

; Center the camera when the run key is pressed.
; Only used if MouseTurning isn't enabled.
ResetCameraWhenRunning = true

; Override the camera sensitivity.
; Min 0.5, max 2.0.
CameraSensitivity = 1.0

; Provides alternative ways to turn the character using the mouse.
; "Modern" aiming mode in the game's settings is recomended.
UseMouseTurning = true

; Choose the MouseTurning type.
; TypeA = The character's rotation is influenced by the camera's position, similar to Resident Evil 6. Using CameraImprovements is recommended.
; TypeB = The character's rotation is directly changed by the mouse, similar to Resident Evil 5.
MouseTurnType = TypeA

; Sensitivity for mouse turning Type B.
; Min 0.5, max 2.0.
TurnTypeBSensitivity = 1.0

; Makes the game use Raw Input for aiming and turning (if MouseTurning is enabled).
; Greatly improves mouse input by removing negative/positive accelerations that were being applied both by the game and by Direct Input.
; This option automatically enables the game's "Modern" aiming mode, and is incompatible with the "Classic" mode.
UseRawMouseInput = true

; When using the "Modern" mouse setting, the game locks the camera position to the aiming position, making both move together.
; Although this is the expected behavior in most games, some people might prefer to keep the original camera behavior while also having the benefits from "Modern" aiming.
; Enabling this will also restore the horizontal aiming sway that was lost when the devs implemented "Modern" aiming.
DetachCameraFromAim = false

; Prevents the camera from being randomly displaced after you zoom with a sniper rifle when using keyboard and mouse.
FixSniperZoom = true

; When zooming in and out with the sniper rifle, this option makes the "focus" animation look similar to how it looks like with a controller.
; Requires EnableGCBlur to be enabled.
FixSniperFocus = true

; Prevents the game from overriding your selection in the "Retry/Load" screen when moving the mouse before confirming an action.
; This bug usually causes people to return to the main menu by mistake, when they actually wanted to just restart from the last checkpoint.
FixRetryLoadMouseSelector = true

[KEYBOARD]
; Game will turn keys invisible for certain unsupported keyboard languages
; Enabling this should make game use English keys for unsupported ones instead
; (if game supports your current language it should still use it however)
FallbackToEnglishKeyIcons = true

; Removes the need to be aiming the weapon before you can reload it.
AllowReloadWithoutAiming = true

; Don't zoom in when reloading without aiming.
; Not usually recomended, since the zooming in and out masks some animation quirks when the reload ends.
ReloadWithoutZoom = false

[CONTROLLER]
; Change the controller sensitivity. For some reason the vanilla game doesn't have an option to change it for controllers, only for the mouse.
; Min 0.5, max 4.0.
ControllerSensitivity = 1.0

; Removes unnecessary deadzones that were added for Xinput controllers.
RemoveExtraXinputDeadzone = true

; Change the Xinput controller deadzone. (Unrelated to the previous option)
; The game's default is 1, but that seems unnecessarily large, so we default to 0.4 instead.
; Min 0.0, max 3.5.
XinputDeadzone = 0.4

; Removes the need to be aiming the weapon before you can reload it.
; Warning: this will also change the reload button based on your current controller config type, 
; since the original button is used for sprinting when not aiming.
; New reload button (Xinput):
; Config Type I: B
; Config Type II & III: X
AllowReloadWithoutAiming = false

; Don't zoom in when reloading without aiming.
; Not usually recomended, since the zooming in and out masks somes animation quirks when the reload ends.
ReloadWithoutZoom = false

[FRAME RATE]
; Fixes the speed of falling items in 60 FPS, making them not fall at double speed.
FixFallingItemsSpeed = true

; Fixes speed of backwards turning when using framerates other than 30FPS.
FixTurningSpeed = true

; When running in 60 FPS, some QTEs require extremely fast button presses to work. This gets even worse in Professional difficulty,
; making it seem almost impossible to survive the minecart and the statue bridge QTEs.
; This fix makes QTEs that involve rapid button presses much more forgiving.
FixQTE = true

; Fixes difference between 30/60FPS on physics applied to Ashley.
FixAshleyBustPhysics = true

; Replaces older math functions in the game with much more optimized equivalents.
; Experimental, can hopefully improve framerate in some areas that had dips.
EnableFastMath = true

; Forces game to fully cache all models in the level after loading in.
; May help with framerate drops when viewing a model for the first time.
; (not fully tested, could cause issues if level has many models to load!)
PrecacheModels = false

[MISC]
; Path to DLL to wrap, comment or leave empty to wrap system DLL
; (only set this if you need re4_tweaks to 'chain-load' another DLL that makes use of the same filename)
;WrappedDLLPath = 

; Allows overriding the costumes, making it possible to combine Normal/Special 1/Special 2 costumes.
; May cause weird visuals in cutscenes.
; Possible costume values:
; Leon: Jacket, Normal, Vest, RPD, Mafia
; Ashley: Normal, Popstar, Armor
; Ada: RE2, Spy, Normal
OverrideCostumes = false
LeonCostume = Jacket
AshleyCostume = Normal
AdaCostume = Normal

; Unlocks the JP-only classic camera angles during Ashley's segment.
AshleyJPCameraAngles = false

; Allows overriding the level of violence in the game.
; Use -1 to leave as your game EXEs default, 0 for low-violence mode (as used in JP/GER version), or 2 for full violence.
ViolenceLevelOverride = -1

; Allows selling the (normally unused) handgun silencer to the merchant.
; If you use a mod that changes the merchant price tables you might want to disable this
; But if you're only using RE4HD you can leave this enabled
AllowSellingHandgunSilencer = true

; Allows the game to display Leon's mafia outfit ("Special 2") on cutscenes.
AllowMafiaLeonCutscenes = true

; Silence Ashley's armored outfit ("Special 2").
; For those who also hate the constant "Clank Clank Clank".
SilenceArmoredAshley = false

; Allows Ashley to Suplex enemies in very specific situations.
; (previously was only possible in the initial NTSC GameCube ver., was patched out in all later ports.)
AllowAshleySuplex = false

; Allows quickturning character to camera direction when wielding Matilda
; (only effective if MouseTurning is disabled)
AllowMatildaQuickturn = true

; Fixes the Ditman glitch, which would allow players to increase their walk speed.
; Not recommended, but mod makers may be interested in enabling this (see Bin32/re4_tweaks/setting_overrides/overrides_info.txt)
FixDitmanGlitch = false

; Changes sprint key to act like a toggle instead of needing to be held.
UseSprintToggle = false

; Disables most of the QTEs, making them pass automatically.
DisableQTE = false

; Unlike the previous option, this only automates the "mashing" QTEs, making them pass automatically. Prompts are still shown!
AutomaticMashingQTE = false

; Whether to skip the Capcom etc intro logos when starting the game.
SkipIntroLogos = false

; Enables the "tool menu" debug menu, present inside the game but unused, and adds a few custom menu entries ("SAVE GAME", "DOF/BLUR MENU", etc).
; Can be opened with the LT+LS button combination (or CTRL+F3 by default on keyboard).
; If enabled on the 1.0.6 debug build it'll apply some fixes to the existing debug menu, fixing AREA JUMP etc, but won't add our custom entries due to lack of space.
; (may have a rare chance to cause a heap corruption crash when loading a save, but if the game loads fine then there shouldn't be any chance of crashing)
EnableDebugMenu = false

; Enables patches/hooks for expanded modding capabilities, such as allowing enemy speed & scale to be defined when spawning.
; Only needed when using mods that specifically require it, otherwise should be left disabled.
; (more info about what this adds can be found here: https://github.com/nipkownix/re4_tweaks/pull/305)
; (modders that require this to be enabled can force it by including a override INI with their mod, see "re4_tweaks/setting_overrides/overrides_info.txt" file)
EnableModExpansion = false

[MEMORY]
; Allocate more memory for SFD movie files, and properly scale its resolution display above 512x336.
; Not tested beyond 1920x1080.
AllowHighResolutionSFD = true

; Allocate more memory for some vertex buffers.
; This prevents a crash that can happen when playing with a high FOV.
RaiseVertexAlloc = true

; Allocate more memory for the inventory screen, preventing crashes with high-poly models inside ss_pzzl.dat.
RaiseInventoryAlloc = true

[HOTKEYS]
; Key combinations for various re4_tweaks features
; Most keys can be combined (requiring multiple to be pressed at the same time) by using + symbol between key names
; (see top of Settings.cpp file for possible key names to use)

; Key combination to open the re4_tweaks config menu
ConfigMenu = F1

; Key combination to open the re4_tweaks debug console (only in certain re4_tweaks builds)
Console = F2

; Key bindings for flipping items in the inventory screen when using keyboard and mouse.
; Normally, you can only rotate them with the keyboard, not flip them. Flipping was possible in the old PC port and is
; possible using a controller.
; * Key combinations not supported
FlipItemUp    = HOME
FlipItemDown  = END
FlipItemLeft  = INSERT
FlipItemRight = PAGEUP

; Key bindings for QTE keys when playing with keyboard and mouse.
; Unlike the "official" way of rebinding keys through usrpInput.ini, this
; option also changes the on-screen prompt to properly match the selected key.
; * Key combinations not supported
QTE_key_1 = D
QTE_key_2 = A

; Key combination to make the "tool menu" debug menu appear
; Requires EnableDebugMenu to be enabled.
DebugMenu = CTRL+F3

; MouseTurning camera modifier. When holding this key combination, MouseTurning is temporarily activated/deactivated.
MouseTurningModifier = ALT

; Key combo for jump tricks during Jet-ski sequence (normally RT+LT on controller)
JetSkiTricks = LMOUSE+RMOUSE

[WARNING]
; This version of RE4 only works properly if played at 30 or 60 FPS. Anything else can and will cause numerous amounts of
; different bugs, most of which aren't even documented. By default, re4_tweaks will warn you about these issues and change
; the FPS to either 30 or 60.
; If you have modified the game's config.ini file and changed the "variableframerate" option to something other than 30 or 60,
; please be aware of the potential issues before turning off this warning.
IgnoreFPSWarning = false

[IMGUI]
; Scale the font used in the configuration menu.
; Min 1.0, max 1.25.
FontSizeScale = 1.000

; Disables the "Press key to open the configuration menu" tooltip.
DisableMenuTip = false

[DEBUG]
; Logs extra information.
VerboseLog = false
NeverHideCursor = false

; Passes the actual elapsed frametime to the game instead of a fixed 30/60FPS frametime.
; Should help reduce slowdown in-game when FPS fails to reach the games framerate setting.
; (experimental, certain things may act strange when using non-fixed frametime, especially audio)
UseDynamicFrametime = false

; Disables any kind of framelimiting.
; Useful for comparing "true" FPS/frametime when making performance-related changes.
; (requires ReplaceFramelimiter = true, recommend DisableVsync too)
DisableFramelimiting = false
)"""";
