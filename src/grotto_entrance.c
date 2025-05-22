#include "modding.h"
#include "global.h"
#include "recomputils.h"
#include "recompconfig.h"

#include "overlays/actors/ovl_Door_Ana/z_door_ana.h"
#include "assets/objects/gameplay_field_keep/gameplay_field_keep.h"

#include "display_lists/gGrottoAlternate/header.h"
#include "display_lists/gGrottoAlternate/model.inc.c"

#define FLAGS (ACTOR_FLAG_UPDATE_DURING_OCARINA)

void DoorAna_Init(Actor* thisx, PlayState* play);
void DoorAna_Destroy(Actor* thisx, PlayState* play);
void DoorAna_Update(Actor* thisx, PlayState* play);
void DoorAna_Draw(Actor* thisx, PlayState* play);

void DoorAna_WaitClosed(DoorAna* this, PlayState* play);
void DoorAna_WaitOpen(DoorAna* this, PlayState* play);

// Patches a function in the base game that's used to check if the player should quickspin.
RECOMP_PATCH void DoorAna_Update(Actor* thisx, PlayState* play) {
    DoorAna* this = (DoorAna*)thisx;

    this->actionFunc(this, play);
    // this->actor.shape.rot.y = BINANG_ROT180(Camera_GetCamDirYaw(GET_ACTIVE_CAM(play)));
}

RECOMP_PATCH void DoorAna_Draw(Actor* thisx, PlayState* play) {
    Gfx_DrawDListXlu(play, gGrottoAlternate_Circle_mesh);
}
