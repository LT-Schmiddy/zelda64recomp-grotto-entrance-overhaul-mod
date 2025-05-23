#include "modding.h"
#include "global.h"
#include "recomputils.h"
#include "recompconfig.h"
#include "string.h"

#include "overlays/actors/ovl_Door_Ana/z_door_ana.h"
#include "assets/objects/gameplay_field_keep/gameplay_field_keep.h"

#include "display_lists/gGrottoAlternate/gGrottoAlternate_Circle.h"
#include "display_lists/gGrottoAlternate/gGrottoAlternate_Circle.c"

#define FLAGS (ACTOR_FLAG_UPDATE_DURING_OCARINA)

void DoorAna_Init(Actor* thisx, PlayState* play);
void DoorAna_Destroy(Actor* thisx, PlayState* play);
void DoorAna_Update(Actor* thisx, PlayState* play);
void DoorAna_Draw(Actor* thisx, PlayState* play);

void DoorAna_WaitClosed(DoorAna* this, PlayState* play);
void DoorAna_WaitOpen(DoorAna* this, PlayState* play);

static DoorAna* captured_this = NULL;
RECOMP_HOOK("DoorAna_Init") void pre_DoorAna_Init(Actor* thisx, PlayState* play) {
    captured_this = (DoorAna*)thisx;
}

RECOMP_HOOK_RETURN("DoorAna_Init") void post_DoorAna_Init() {
    f32 rot = captured_this->actor.world.pos.x + captured_this->actor.world.pos.z * captured_this->actor.world.pos.y ;
    u32 rot_bytes;   
    memcpy (&rot_bytes, &rot, sizeof(u32));
    captured_this->actor.shape.rot.y = rot_bytes;
    // recomp_printf("Grotto Angle: %i\n", captured_this->actor.shape.rot.y);
}


// Patches a function in the base game that's used to check if the player should quickspin.
RECOMP_PATCH void DoorAna_Update(Actor* thisx, PlayState* play) {
    DoorAna* this = (DoorAna*)thisx;

    this->actionFunc(this, play);
    // this->actor.shape.rot.y = BINANG_ROT180(Camera_GetCamDirYaw(GET_ACTIVE_CAM(play)));
}

RECOMP_PATCH void DoorAna_Draw(Actor* thisx, PlayState* play) {
    Gfx_DrawDListOpa(play, gGrottoAlternate_Circle);
}
