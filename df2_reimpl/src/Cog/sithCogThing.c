#include "sithCogThing.h"

#include <stdint.h>
#include "World/sithSector.h"
#include "World/sithThing.h"
#include "World/sithTrackThing.h"
#include "World/sithInventory.h"
#include "Engine/rdThing.h"
#include "Engine/sithNet.h"
#include "Engine/sithSurface.h"
#include "Engine/sithTime.h"
//#include "Engine/rdSurface.h"

#include "stdPlatform.h"
#include "Win95/DebugConsole.h"

void sithCogThing_createThingAtPos_nr(sithCog *ctx);

static void (*sithCogThing_DetachThing)(sithCog* ctx) = (void*)0x00503490;
static void (*sithCogThing_GetAttachFlags)(sithCog* ctx) = (void*)0x005034F0;
static void (*sithCogThing_AttachThingToSurf)(sithCog* ctx) = (void*)0x00503520;
static void (*sithCogThing_AttachThingToThing)(sithCog* ctx) = (void*)0x00503590;
static void (*sithCogThing_AttachThingToThingEx)(sithCog* ctx) = (void*)0x00503600;
static void (*sithCogThing_PlayMode)(sithCog* ctx) = (void*)0x00503680;
static void (*sithCogThing_PlayKey)(sithCog* ctx) = (void*)0x00503740;
static void (*sithCogThing_StopKey)(sithCog* ctx) = (void*)0x00503870;
static void (*sithCogThing_SetThingModel)(sithCog* ctx) = (void*)0x00503920;
static void (*sithCogThing_GetThingModel)(sithCog* ctx) = (void*)0x005039B0;
static void (*sithCogThing_SetArmedMode)(sithCog* ctx) = (void*)0x00503A00;
static void (*sithCogThing_GetThingFlags)(sithCog* ctx) = (void*)0x00503A70;
static void (*sithCogThing_SetThingFlags)(sithCog* ctx) = (void*)0x00503AA0;
static void (*sithCogThing_ClearThingFlags)(sithCog* ctx) = (void*)0x00503B00;
static void (*sithCogThing_TeleportThing)(sithCog* ctx) = (void*)0x00503B60;
static void (*sithCogThing_SetThingType)(sithCog* ctx) = (void*)0x00503C50;
static void (*sithCogThing_GetCollideType)(sithCog* ctx) = (void*)0x00503C80;
static void (*sithCogThing_SetCollideType)(sithCog* ctx) = (void*)0x00503CB0;
static void (*sithCogThing_FirstThingInSector)(sithCog* ctx) = (void*)0x00503D10;
static void (*sithCogThing_NextThingInSector)(sithCog* ctx) = (void*)0x00503D60;
static void (*sithCogThing_PrevThingInSector)(sithCog* ctx) = (void*)0x00503DA0;
static void (*sithCogThing_GetInvMin)(sithCog* ctx) = (void*)0x00503DE0;
static void (*sithCogThing_GetInvMax)(sithCog* ctx) = (void*)0x00503E40;
static void (*sithCogThing_sub_503EA0)(sithCog* ctx) = (void*)0x00503EA0;
static void (*sithCogThing_sub_503EE0)(sithCog* ctx) = (void*)0x00503EE0;
static void (*sithCogThing_sub_503F40)(sithCog* ctx) = (void*)0x00503F40;
static void (*sithCogThing_PathMovePause)(sithCog* ctx) = (void*)0x00503FA0;
static void (*sithCogThing_SetHeadlightIntensity)(sithCog* ctx) = (void*)0x00503FF0;
static void (*sithCogThing_GetHeadlightIntensity)(sithCog* ctx) = (void*)0x00504050;
static void (*sithCogThing_IsThingVisible)(sithCog* ctx) = (void*)0x005040A0;
static void (*sithCogThing_PathMoveResume)(sithCog* ctx) = (void*)0x005040E0;
static void (*sithCogThing_SetCurInvWeapon)(sithCog* ctx) = (void*)0x00504130;
static void (*sithCogThing_GetCurInvWeapon)(sithCog* ctx) = (void*)0x00504160;
static void (*sithCogThing_SetThingGeoMode)(sithCog* ctx) = (void*)0x005041A0;
static void (*sithCogThing_GetThingGeoMode)(sithCog* ctx) = (void*)0x005041D0;
static void (*sithCogThing_SetThingLightMode)(sithCog* ctx) = (void*)0x00504200;
static void (*sithCogThing_GetThingLightMode)(sithCog* ctx) = (void*)0x00504230;
static void (*sithCogThing_SetThingTexMode)(sithCog* ctx) = (void*)0x00504260;
static void (*sithCogThing_GetThingTexMode)(sithCog* ctx) = (void*)0x00504290;
static void (*sithCogThing_SetThingCurGeoMode)(sithCog* ctx) = (void*)0x005042C0;
static void (*sithCogThing_GetThingCurGeoMode)(sithCog* ctx) = (void*)0x00504320;
static void (*sithCogThing_SetThingCurLightmode)(sithCog* ctx) = (void*)0x00504350;
static void (*sithCogThing_GetThingCurLightMode)(sithCog* ctx) = (void*)0x00504380;
static void (*sithCogThing_SetThingCurTexMode)(sithCog* ctx) = (void*)0x005043B0;
static void (*sithCogThing_GetThingCurTexMode)(sithCog* ctx) = (void*)0x005043E0;
static void (*sithCogThing_SetActorExtraSpeed)(sithCog* ctx) = (void*)0x00504410;
static void (*sithCogThing_GetThingTemplate)(sithCog* ctx) = (void*)0x00504440;
static void (*sithCogThing_SetLifeLeft)(sithCog* ctx) = (void*)0x00504480;
static void (*sithCogThing_GetLifeLeft)(sithCog* ctx) = (void*)0x00504500;
static void (*sithCogThing_SetThingThrust)(sithCog* ctx) = (void*)0x00504540;
static void (*sithCogThing_GetThingThrust)(sithCog* ctx) = (void*)0x005045A0;
static void (*sithCogThing_AmputateJoint)(sithCog* ctx) = (void*)0x005045D0;
static void (*sithCogThing_SetActorWeapon)(sithCog* ctx) = (void*)0x00504620;
static void (*sithCogThing_GetActorWeapon)(sithCog* ctx) = (void*)0x00504680;
static void (*sithCogThing_GetPhysicsFlags)(sithCog* ctx) = (void*)0x005046F0;
static void (*sithCogThing_SetPhysicsFlags)(sithCog* ctx) = (void*)0x00504730;
static void (*sithCogThing_ClearPhysicsFlags)(sithCog* ctx) = (void*)0x005047A0;
static void (*sithCogThing_SkillTarget)(sithCog* ctx) = (void*)0x005047E0;
static void (*sithCogThing_ParseArg)(sithCog* ctx) = (void*)0x005048D0;
static void (*sithCogThing_SetThingRotVel)(sithCog* ctx) = (void*)0x00504950;
static void (*sithCogThing_GetThingRotVel)(sithCog* ctx) = (void*)0x005049D0;
static void (*sithCogThing_SetThingLook)(sithCog* ctx) = (void*)0x00504A10;
static void (*sithCogThing_IsCrouching)(sithCog* ctx) = (void*)0x00504A90;
static void (*sithCogThing_GetThingClassCog)(sithCog* ctx) = (void*)0x00504AE0;
static void (*sithCogThing_SetThingClassCog)(sithCog* ctx) = (void*)0x00504B20;
static void (*sithCogThing_GetThingCaptureCog)(sithCog* ctx) = (void*)0x00504B50;
static void (*sithCogThing_SetThingCaptureCog)(sithCog* ctx) = (void*)0x00504B90;
static void (*sithCogThing_GetThingRespawn)(sithCog* ctx) = (void*)0x00504BC0;
static void (*sithCogThing_GetThingSignature)(sithCog* ctx) = (void*)0x00504BF0;
static void (*sithCogThing_SetThingAttachFlags)(sithCog* ctx) = (void*)0x00504C20;
static void (*sithCogThing_ClearThingAttachFlags)(sithCog* ctx) = (void*)0x00504C80;
static void (*sithCogThing_GetParticleSize)(sithCog* ctx) = (void*)0x00504CE0;
static void (*sithCogThing_SetParticleSize)(sithCog* ctx) = (void*)0x00504D20;
static void (*sithCogThing_GetParticleGrowthSpeed)(sithCog* ctx) = (void*)0x00504D60;
static void (*sithCogThing_SetParticleGrowthSpeed)(sithCog* ctx) = (void*)0x00504DA0;
static void (*sithCogThing_GetParticleTimeoutRate)(sithCog* ctx) = (void*)0x00504DE0;
static void (*sithCogThing_SetParticleTimeoutRate)(sithCog* ctx) = (void*)0x00504E20;
static void (*sithCogThing_GetXFlags)(sithCog* ctx) = (void*)0x00504E60;
static void (*sithCogThing_SetXFlags)(sithCog* ctx) = (void*)0x00504EF0;
static void (*sithCogThing_ClearXFlags)(sithCog* ctx) = (void*)0x00504F80;
static void (*sithCogThing_TakeItem)(sithCog* ctx) = (void*)0x00505020;
static void (*sithCogThing_HasLos)(sithCog* ctx) = (void*)0x00505060;
static void (*sithCogThing_GetThingFireOffset)(sithCog* ctx) = (void*)0x005050C0;
static void (*sithCogThing_SetThingFireOffset)(sithCog* ctx) = (void*)0x00505100;
static void (*sithCogThing_GetThingUserdata)(sithCog* ctx) = (void*)0x00505150;
static void (*sithCogThing_SetThingUserdata)(sithCog* ctx) = (void*)0x00505190;
static void (*sithCogThing_GetThingCollideSize)(sithCog* ctx) = (void*)0x005051C0;
static void (*sithCogThing_SetThingCollideSize)(sithCog* ctx) = (void*)0x00505200;
static void (*sithCogThing_GetThingMoveSize)(sithCog* ctx) = (void*)0x00505230;
static void (*sithCogThing_SetThingMoveSize)(sithCog* ctx) = (void*)0x00505270;
static void (*sithCogThing_GetThingMass)(sithCog* ctx) = (void*)0x005052A0;
static void (*sithCogThing_SetThingMass)(sithCog* ctx) = (void*)0x005052E0;
static void (*sithCogThing_SyncThingPos)(sithCog* ctx) = (void*)0x00505340;
static void (*sithCogThing_SyncThingAttachment)(sithCog* ctx) = (void*)0x00505360;
static void (*sithCogThing_SyncThingState)(sithCog* ctx) = (void*)0x00505390;
static void (*sithCogThing_GetMajorMode)(sithCog* ctx) = (void*)0x005053B0;

void sithCogThing_GetThingType(sithCog *ctx)
{
    sithThing *thing;

    thing = sithCogVm_PopThing(ctx);
    if ( thing )
        sithCogVm_PushInt(ctx, thing->thingType);
    else
        sithCogVm_PushInt(ctx, -1);
}

void sithCogThing_CreateThing(sithCog *ctx)
{
    sithThing *v1; // esi
    sithThing *v2; // ebx
    sithThing *v3; // edi

    v1 = sithCogVm_PopThing(ctx);
    v2 = sithCogVm_PopTemplate(ctx);
    if ( v1 && v1->thingType && v1->sector && v2 && (v3 = sithThing_SpawnTemplate(v2, v1)) != 0 )
    {
        if ( sithCogVm_isMultiplayer )
        {
            if ( !(ctx->flags & 0x200) )
            {
                if ( ctx->trigId != SITH_MESSAGE_STARTUP && ctx->trigId != SITH_MESSAGE_SHUTDOWN )
                    sithSector_cogMsg_SendCreateThing(v2, v3, v1, 0, 0, 0, 255, 1);
            }
        }
        sithCogVm_PushInt(ctx, v3->thingIdx);
    }
    else
    {
        sithCogVm_PushInt(ctx, -1);
    }
}


void sithCogThing_CreateThingNr(sithCog *ctx)
{
    sithThing *v1; // esi
    sithThing *v2; // ebx
    sithThing *v3; // edi

    v1 = sithCogVm_PopThing(ctx);
    v2 = sithCogVm_PopTemplate(ctx);
    if ( v1 && v1->thingType && v1->sector && v2 && (v3 = sithThing_SpawnTemplate(v2, v1)) != 0 )
    {
        if ( sithCogVm_isMultiplayer )
        {
            if ( !(ctx->flags & 0x200) )
            {
                if ( ctx->trigId != SITH_MESSAGE_STARTUP && ctx->trigId != SITH_MESSAGE_SHUTDOWN )
                    sithSector_cogMsg_SendCreateThing(v2, v3, v1, 0, 0, 0, 255, 1);
            }
        }
        sithCogVm_PushInt(ctx, v3->thingIdx);
    }
    else
    {
        sithCogVm_PushInt(ctx, -1);
    }
}

void sithCogThing_createThingUnused(sithCog *ctx)
{
    sithThing *v1; // esi
    sithThing *v2; // ebx
    sithThing *v3; // edi
    int v6; // [esp+18h] [ebp+8h]

    v1 = sithCogVm_PopThing(ctx);
    v2 = sithCogVm_PopTemplate(ctx);
    if ( v1 && v1->thingType && v1->sector && v2 && (v3 = sithThing_SpawnTemplate(v2, v1)) != 0 )
    {
        if ( sithCogVm_isMultiplayer )
        {
            if ( !(ctx->flags & 0x200) )
            {
                if ( ctx->trigId != SITH_MESSAGE_STARTUP && ctx->trigId != SITH_MESSAGE_SHUTDOWN )
                    sithSector_cogMsg_SendCreateThing(v2, v3, v1, 0, 0, 0, 255, v6);
            }
        }
        sithCogVm_PushInt(ctx, v3->thingIdx);
    }
    else
    {
        sithCogVm_PushInt(ctx, -1);
    }
}

void sithCogThing_CreateThingAtPos(sithCog *ctx)
{
    sithCogThing_createThingAtPos_nr(ctx);
}

void sithCogThing_CreateThingAtPosNr(sithCog *ctx)
{
    sithCogThing_createThingAtPos_nr(ctx);
}

void sithCogThing_createThingAtPos_nr(sithCog *ctx)
{
    sithSector *popSector; // ebp
    sithThing *popTemplate; // eax
    rdVector3 *v5; // eax
    rdVector3 *v6; // ecx
    sithThing *v7; // ebx
    rdVector3 a1; // [esp+10h] [ebp-54h]
    rdVector3 pos; // [esp+1Ch] [ebp-48h]
    rdVector3 rot; // [esp+28h] [ebp-3Ch]
    rdMatrix34 a3; // [esp+34h] [ebp-30h]
    int a8; // [esp+6Ch] [ebp+8h]

    sithCogVm_PopVector3(ctx, &rot);
    sithCogVm_PopVector3(ctx, &pos);
    popSector = sithCogVm_PopSector(ctx);
    popTemplate = sithCogVm_PopTemplate(ctx);
    if ( !popTemplate || !popSector )
    {
        sithCogVm_PushInt(ctx, -1);
        return;
    }
    if (popTemplate->rdthing.type == RD_THINGTYPE_MODEL)
    {
        a1 = popTemplate->rdthing.model3->insertOffset;
    }
    else if (popTemplate->rdthing.type == RD_THINGTYPE_SPRITE3)
    {
        a1 = popTemplate->rdthing.sprite3->offset;
    }
    else
    {
        a1.x = 0.0;
        a1.y = 0.0;
        a1.z = 0.0;
    }

    rdMatrix_BuildRotate34(&a3, &rot);
    rdMatrix_TransformVector34Acc(&a1, &a3);
    rdVector_Add3Acc(&pos, &a1);
    v7 = sithThing_SpawnThingInSector(popTemplate, &pos, &a3, popSector, 0);
    if ( v7 )
    {
        if ( sithCogVm_isMultiplayer )
        {
            if ( !(ctx->flags & 0x200) )
            {
                if ( ctx->trigId != SITH_MESSAGE_STARTUP && ctx->trigId != SITH_MESSAGE_SHUTDOWN )
                    sithSector_cogMsg_SendCreateThing(popTemplate, v7, 0, popSector, (int *)&pos, (int *)&rot, 255, a8);
            }
        }
        sithCogVm_PushInt(ctx, v7->thingIdx);
    }
    else
    {
        sithCogVm_PushInt(ctx, -1);
    }
}

void sithCogThing_DamageThing(sithCog *ctx)
{
    sithThing* thing = sithCogVm_PopThing(ctx);
    int a4 = sithCogVm_PopInt(ctx);
    float a5 = sithCogVm_PopFlex(ctx);
    sithThing* thing2 = sithCogVm_PopThing(ctx);

    if ( a5 > 0.0 && thing2 )
    {
        if ( !thing )
            thing = thing2;
        if ( sithCogVm_isMultiplayer )
        {
            if ( !(ctx->flags & 0x200) )
            {
                if ( ctx->trigId != SITH_MESSAGE_STARTUP && ctx->trigId != SITH_MESSAGE_SHUTDOWN )
                {
                    if ( net_isServer )
                        sithSector_cogMsg_SendDamage(thing2, thing, a5, a4, -1, 1);
                }
            }
        }
        sithCogVm_PushFlex(ctx, sithThing_Damage(thing2, thing, a5, a4));
    }
    else
    {
        sithCogVm_PushInt(ctx, -1);
    }
}

void sithCogThing_HealThing(sithCog *ctx)
{
    float amt = sithCogVm_PopFlex(ctx);
    sithThing* thing = sithCogVm_PopThing(ctx);
    if (amt > 0.0 && thing && (thing->thingType == THINGTYPE_ACTOR || thing->thingType == THINGTYPE_PLAYER))
    {
        thing->actorParams.health += amt;
        if ( thing->actorParams.health > thing->actorParams.maxHealth)
            thing->actorParams.health = thing->actorParams.maxHealth;
    }
}

void sithCogThing_GetThingHealth(sithCog *ctx)
{
    sithThing* thing = sithCogVm_PopThing(ctx);

    if ( thing && (thing->thingType == THINGTYPE_ACTOR || thing->thingType == THINGTYPE_PLAYER) )
        sithCogVm_PushFlex(ctx, thing->actorParams.health);
    else
        sithCogVm_PushFlex(ctx, -1.0);
}

void sithCogThing_SetHealth(sithCog *ctx)
{
    float amt = sithCogVm_PopFlex(ctx);
    sithThing* thing = sithCogVm_PopThing(ctx);

    if (thing && (thing->thingType == THINGTYPE_ACTOR || thing->thingType == THINGTYPE_PLAYER))
        thing->actorParams.health = amt;
}

void sithCogThing_DestroyThing(sithCog *ctx)
{
    sithThing* thing = sithCogVm_PopThing(ctx);
    if (!thing)
        return;

    if (sithCogVm_isMultiplayer 
        && !(ctx->flags & 0x200) 
        && ctx->trigId != SITH_MESSAGE_STARTUP 
        && ctx->trigId != SITH_MESSAGE_SHUTDOWN )
        sithSector_cogMsg_SendDestroyThing(thing->thing_id, -1);

    sithThing_Destroy(thing);
}

void sithCogThing_JumpToFrame(sithCog *ctx)
{
    sithSector* sector = sithCogVm_PopSector(ctx);
    uint32_t frame = sithCogVm_PopInt(ctx);
    sithThing* thing = sithCogVm_PopThing(ctx);

    if ( thing && sector && thing->move_type == 2 && frame < thing->trackParams.loadedFrames )
    {
        if ( thing->sector && sector != thing->sector )
            sithThing_LeaveSector(thing);

        if ( thing->attach_flags )
            sithThing_DetachThing_(thing);

        rdMatrix_BuildRotate34(&thing->lookOrientation, &thing->trackParams.frames[frame].rot);
        rdVector_Copy3(&thing->position, &thing->trackParams.frames[frame].pos);

        if ( !thing->sector )
            sithThing_EnterSector(thing, sector, 1, 0);
    }
}

void sithCogThing_MoveToFrame(sithCog *ctx)
{
    float speed = sithCogVm_PopFlex(ctx) * 0.1;
    int frame = sithCogVm_PopInt(ctx);
    sithThing* thing = sithCogVm_PopThing(ctx);
    if ( thing && thing->move_type == MOVETYPE_PATH && thing->trackParams.loadedFrames > frame )
    {
        if ( speed == 0.0 )
            speed = 0.5;

        sithTrackThing_MoveToFrame(thing, frame, speed);

        if (sithCogVm_isMultiplayer 
            && !(ctx->flags & 0x200) 
            && ctx->trigId != SITH_MESSAGE_STARTUP 
            && ctx->trigId != SITH_MESSAGE_SHUTDOWN )
            sithSector_cogMsg_SendSyncThingFrame(thing, frame, speed, 0, -1, 255);
    }
}

void sithCogThing_SkipToFrame(sithCog *ctx)
{
    float speed = sithCogVm_PopFlex(ctx) * 0.1;
    int frame = sithCogVm_PopInt(ctx);
    sithThing* thing = sithCogVm_PopThing(ctx);
    if ( thing && thing->move_type == MOVETYPE_PATH && thing->trackParams.loadedFrames > frame )
    {
        if ( speed == 0.0 )
            speed = 0.5;

        sithTrackThing_SkipToFrame(thing, frame, speed);

        if (sithCogVm_isMultiplayer 
            && !(ctx->flags & 0x200) 
            && ctx->trigId != SITH_MESSAGE_STARTUP 
            && ctx->trigId != SITH_MESSAGE_SHUTDOWN )
            sithSector_cogMsg_SendSyncThingFrame(thing, frame, speed, 1, -1, 255);
    }
}

void sithCogThing_RotatePivot(sithCog *ctx)
{
    float speed = sithCogVm_PopFlex(ctx);
    uint32_t frame = sithCogVm_PopInt(ctx);
    sithThing* thing = sithCogVm_PopThing(ctx);

    if ( speed == 0.0 )
        speed = 1.0;

    if ( thing && thing->move_type == MOVETYPE_PATH && thing->trackParams.loadedFrames > frame )
    {
        rdVector3* pos = &thing->trackParams.frames[frame].pos;
        rdVector3* rot = &thing->trackParams.frames[frame].rot;
        if ( speed <= 0.0 )
        {
            rdVector3 negRot;

            rdVector_Neg3(&negRot, rot);
            float negSpeed = -speed;
            sithTrackThing_RotatePivot(thing, pos, &negRot, negSpeed);
        }
        else
        {
            sithTrackThing_RotatePivot(thing, pos, rot, speed);
        }
    }
}

void sithCogThing_Rotate(sithCog *ctx)
{
    rdVector3 rot;

    sithCogVm_PopVector3(ctx, &rot);
    sithThing* thing = sithCogVm_PopThing(ctx);

    if (thing)
    {
        if ( thing->move_type == MOVETYPE_PATH )
            sithTrackThing_Rotate(thing, &rot);
    }
}

void sithCogThing_GetThingLight(sithCog *ctx)
{
    sithThing *thing;

    thing = sithCogVm_PopThing(ctx);
    if ( thing )
        sithCogVm_PushFlex(ctx, thing->light);
    else
        sithCogVm_PushFlex(ctx, -1.0);
}

void sithCogThing_SetThingLight(sithCog *ctx)
{
    float idk = sithCogVm_PopFlex(ctx);
    float light = sithCogVm_PopFlex(ctx);
    sithThing* thing = sithCogVm_PopThing(ctx);

    if ( thing && light >= 0.0 )
    {
        if ( idk == 0.0 )
        {
            thing->light = light;
            if ( light != 0.0 )
            {
                thing->thingflags |= SITH_TF_LIGHT;
            }
        }
        else
        {
            sithSurface_SetThingLight(thing, light, idk, 0);
        }
    }
}

void sithCogThing_ThingLightAnim(sithCog *ctx)
{
    sithThing *thing; // ecx
    float idk_; // ST08_4
    rdSurface *surface; // eax
    float idk; // [esp+Ch] [ebp-8h]
    float light2; // [esp+10h] [ebp-4h]
    float light; // [esp+18h] [ebp+4h]

    idk = sithCogVm_PopFlex(ctx);
    light2 = sithCogVm_PopFlex(ctx);
    light = sithCogVm_PopFlex(ctx);
    thing = sithCogVm_PopThing(ctx);
    if ( thing
      && light2 >= (double)light
      && idk > 0.0
      && (idk_ = idk * 0.5, thing->light = light, (surface = sithSurface_SetThingLight(thing, light2, idk_, 1)) != 0) )
    {
        sithCogVm_PushInt(ctx, surface->field_0);
    }
    else
    {
        sithCogVm_PushInt(ctx, -1);
    }
}

void sithCogThing_WaitForStop(sithCog *ctx)
{
    sithThing* thing = sithCogVm_PopThing(ctx);

    if ( thing && thing->move_type == MOVETYPE_PATH && thing->trackParams.field_C & 3 )
    {
        int idx = thing->thingIdx;
        ctx->script_running = 3;
        ctx->wakeTimeMs = idx;

        if ( ctx->flags & 1 )
        {
            _sprintf(std_genBuffer, "Cog %s: Waiting for stop on object %d.\n", ctx->cogscript_fpath, idx);
            DebugConsole_Print(std_genBuffer);
        }
    }
}

void sithCogThing_GetThingSector(sithCog *ctx)
{
    sithThing *thing;
    sithSector *sector;

    thing = sithCogVm_PopThing(ctx);
    if ( thing && (sector = thing->sector) != 0 )
        sithCogVm_PushInt(ctx, sector->id);
    else
        sithCogVm_PushInt(ctx, -1);
}

void sithCogThing_GetCurFrame(sithCog *ctx)
{
    sithThing* thing = sithCogVm_PopThing(ctx);

    if ( thing && thing->move_type == MOVETYPE_PATH )
        sithCogVm_PushInt(ctx, thing->curframe);
    else
        sithCogVm_PushInt(ctx, 0);
}

void sithCogThing_GetGoalFrame(sithCog *ctx)
{
    sithThing* thing = sithCogVm_PopThing(ctx);

    if ( thing && thing->move_type == MOVETYPE_PATH )
        sithCogVm_PushInt(ctx, thing->goalframe);
    else
        sithCogVm_PushInt(ctx, 0);
}

void sithCogThing_StopThing(sithCog *ctx)
{
    sithThing* thing = sithCogVm_PopThing(ctx);

    if (!thing)
        return;

    if ( thing->move_type == MOVETYPE_PATH )
    {
        sithTrackThing_Stop(thing);
        if (sithCogVm_isMultiplayer && !(ctx->flags & 0x200) && ctx->trigId != SITH_MESSAGE_STARTUP && ctx->trigId != SITH_MESSAGE_SHUTDOWN)
            sithSector_cogMsg_SendSyncThingFrame(thing, 0, 0.0, 2, -1, 255);
    }
    else if (thing->move_type == MOVETYPE_PHYSICS)
    {
        sithSector_StopPhysicsThing(thing);
    }
}

void sithCogThing_IsMoving(sithCog *ctx)
{
    sithThing* thing = sithCogVm_PopThing(ctx);
    if ( !thing || thing->thingType == THINGTYPE_FREE )
    {
        sithCogVm_PushInt(ctx, 0);
        return;
    }

    if ( thing->move_type == MOVETYPE_PHYSICS )
    {
        if ( thing->physicsParams.vel.x != 0.0 || thing->physicsParams.vel.y != 0.0 || thing->physicsParams.vel.z != 0.0 )
        {
            sithCogVm_PushInt(ctx, 1);
            return;
        }
    }
    else if ( thing->move_type == MOVETYPE_PATH )
    {
        sithCogVm_PushInt(ctx, thing->trackParams.field_C & 3);
        return;
    }

    sithCogVm_PushInt(ctx, 0);
}

void sithCogThing_SetThingPulse(sithCog *ctx)
{
    float pulseSecs = sithCogVm_PopFlex(ctx);
    sithThing* thing = sithCogVm_PopThing(ctx);
    if (!thing)
        return;

    if ( pulseSecs == 0.0 )
    {
        thing->pulse_end_ms = 0;
        thing->thingflags &= ~SITH_TF_PULSE;
        thing->pulse_ms = 0;
    }
    else
    {
        thing->thingflags |= SITH_TF_PULSE;
        thing->pulse_ms = (int)(pulseSecs * 1000.0);
        thing->pulse_end_ms = thing->pulse_ms + sithTime_curMs;
    }
}

void sithCogThing_SetThingTimer(sithCog *ctx)
{
    float timerSecs = sithCogVm_PopFlex(ctx);
    sithThing* thing = sithCogVm_PopThing(ctx);
    if (!thing)
        return;

    if ( timerSecs == 0.0 )
    {
        thing->timer = 0;
        thing->thingflags &= ~SITH_TF_TIMER;
    }
    else
    {
        thing->thingflags |= SITH_TF_TIMER;
        thing->timer = sithTime_curMs + (uint32_t)(timerSecs * 1000.0);
    }
}

void sithCogThing_CaptureThing(sithCog *ctx)
{
    sithThing* thing = sithCogVm_PopThing(ctx);
    if (thing)
    {
        thing->capture_cog = ctx;
        thing->thingflags |= SITH_TF_CAPTURED;
    }
}

void sithCogThing_ReleaseThing(sithCog *ctx)
{
    sithThing* thing = sithCogVm_PopThing(ctx);
    if ( thing )
    {
        sithCog* class_cog = thing->class_cog;
        thing->capture_cog = NULL;
        if ( !class_cog && !sithThing_Release(thing) )
        {
            thing->thingflags &= ~SITH_TF_CAPTURED;
        }
    }
}

void sithCogThing_GetThingParent(sithCog *ctx)
{
    sithThing* thing;
    sithThing* parent;

    thing = sithCogVm_PopThing(ctx);
    if ( thing && (parent = sithThing_GetParent(thing)) != 0 )
        sithCogVm_PushInt(ctx, parent->thingIdx);
    else
        sithCogVm_PushInt(ctx, -1);
}

void sithCogThing_GetThingPos(sithCog *ctx)
{
    sithThing *thing; // eax

    thing = sithCogVm_PopThing(ctx);
    if ( thing )
        sithCogVm_PushVector3(ctx, &thing->position);
    else
        sithCogVm_PushVector3(ctx, (rdVector3*)&rdroid_zeroVector3);
}

void sithCogThing_SetThingPos(sithCog *ctx)
{
    rdVector3 poppedVec;

    sithCogVm_PopVector3(ctx, &poppedVec);
    sithThing* thing = sithCogVm_PopThing(ctx);
    if (thing)
    {
        rdVector_Copy3(&thing->position, &poppedVec);
        if (sithCogVm_isMultiplayer 
            && !(ctx->flags & 0x200)
            && ctx->trigId != SITH_MESSAGE_STARTUP 
            && ctx->trigId != SITH_MESSAGE_SHUTDOWN)
        {
            sithSector_cogMsg_SendTeleportThing(thing, -1, 1);
        }
        sithCogVm_PushInt(ctx, 1);
    }
    else
    {
        sithCogVm_PushInt(ctx, 0);
    }
}

void sithCogThing_GetInv(sithCog *ctx)
{
    unsigned int binIdx;
    sithThing *playerThing;

    binIdx = sithCogVm_PopInt(ctx);
    playerThing = sithCogVm_PopThing(ctx);
    if ( playerThing 
         && playerThing->thingType == THINGTYPE_PLAYER 
         && playerThing->actorParams.playerinfo 
         && binIdx < 200 )
    {
        sithCogVm_PushFlex(ctx, sithInventory_GetBinAmount(playerThing, binIdx));
    }
    else
    {
        sithCogVm_PushFlex(ctx, 0.0);
    }
}

void sithCogThing_SetInv(sithCog *ctx)
{
    float amt = sithCogVm_PopFlex(ctx);
    uint32_t binIdx = sithCogVm_PopInt(ctx);
    sithThing* playerThing = sithCogVm_PopThing(ctx);

    if ( playerThing 
         && playerThing->thingType == THINGTYPE_PLAYER 
         && playerThing->actorParams.playerinfo 
         && binIdx < 200 )
        sithInventory_SetBinAmount(playerThing, binIdx, amt);
}

void sithCogThing_ChangeInv(sithCog *ctx)
{
    float amt = sithCogVm_PopFlex(ctx);
    uint32_t binIdx = sithCogVm_PopInt(ctx);
    sithThing* playerThing = sithCogVm_PopThing(ctx);

    if ( playerThing 
         && playerThing->thingType == THINGTYPE_PLAYER 
         && playerThing->actorParams.playerinfo 
         && binIdx < 200 )
    {
        sithCogVm_PushFlex(ctx, sithInventory_ChangeInv(playerThing, binIdx, amt));
    }
    else
    {
        sithCogVm_PushFlex(ctx, 0.0);
    }
}

void sithCogThing_GetInvCog(sithCog *ctx)
{
    unsigned int binIdx;
    sithThing *playerThing;
    sithItemDescriptor *desc;
    sithCog *descCog;

    binIdx = sithCogVm_PopInt(ctx);
    playerThing = sithCogVm_PopThing(ctx);
    if ( playerThing
      && playerThing->thingType == THINGTYPE_PLAYER
      && playerThing->actorParams.playerinfo
      && (desc = sithInventory_GetItemDesc(playerThing, binIdx), binIdx < 200)
      && desc
      && (descCog = desc->cog) != 0 )
    {
        sithCogVm_PushInt(ctx, descCog->selfCog);
    }
    else
    {
        sithCogVm_PushInt(ctx, -1);
    }
}

void sithCogThing_GetThingVel(sithCog *ctx)
{
    rdVector3 retval;

    rdVector_Copy3(&retval, &rdroid_zeroVector3);
    sithThing* thing = sithCogVm_PopThing(ctx);
    if ( thing )
    {
        if ( thing->move_type == MOVETYPE_PHYSICS)
        {
            rdVector_Copy3(&retval, &thing->physicsParams.vel);
        }
        else if ( thing->move_type == MOVETYPE_PATH )
        {
            rdVector_Scale3(&retval, &thing->trackParams.vel, thing->trackParams.field_20);
        }
        sithCogVm_PushVector3(ctx, &retval);
    }
    else
    {
        sithCogVm_PushVector3(ctx, (rdVector3*)&rdroid_zeroVector3);
    }
}

void sithCogThing_SetThingVel(sithCog *ctx)
{
    rdVector3 poppedVec;

    sithCogVm_PopVector3(ctx, &poppedVec);
    sithThing* thing = sithCogVm_PopThing(ctx);
    if ( thing && thing->move_type == MOVETYPE_PHYSICS)
    {
        rdVector_Copy3(&thing->physicsParams.vel, &poppedVec);
        if ( sithCogVm_isMultiplayer 
             && !(ctx->flags & 0x200)
             && ctx->trigId != SITH_MESSAGE_STARTUP 
             && ctx->trigId != SITH_MESSAGE_SHUTDOWN)
        {
            sithThing_SyncThingPos((int)thing, 1);
        }
    }
}

void sithCogThing_ApplyForce(sithCog *ctx)
{
    rdVector3 poppedVec;

    sithCogVm_PopVector3(ctx, &poppedVec);
    sithThing* thing = sithCogVm_PopThing(ctx);
    if ( thing && thing->move_type == MOVETYPE_PHYSICS)
    {
        sithSector_ThingApplyForce(thing, &poppedVec);
        if ( sithCogVm_isMultiplayer 
             && !(ctx->flags & 0x200)
             && ctx->trigId != SITH_MESSAGE_STARTUP 
             && ctx->trigId != SITH_MESSAGE_SHUTDOWN)
        {
            sithThing_SyncThingPos((int)thing, 1);
        }
    }
}

void sithCogThing_AddThingVel(sithCog *ctx)
{
    rdVector3 poppedVec;

    sithCogVm_PopVector3(ctx, &poppedVec);
    sithThing* thing = sithCogVm_PopThing(ctx);
    if ( thing && thing->move_type == MOVETYPE_PHYSICS)
    {
        rdVector_Add3Acc(&thing->physicsParams.vel, &poppedVec);
        if ( sithCogVm_isMultiplayer 
             && !(ctx->flags & 0x200)
             && ctx->trigId != SITH_MESSAGE_STARTUP 
             && ctx->trigId != SITH_MESSAGE_SHUTDOWN)
        {
            sithThing_SyncThingPos((int)thing, 1);
        }
    }
}

void sithCogThing_GetThingLvec(sithCog *ctx)
{
    sithThing *thing; // eax

    thing = sithCogVm_PopThing(ctx);
    if ( thing )
        sithCogVm_PushVector3(ctx, &thing->lookOrientation.lvec);
    else
        sithCogVm_PushVector3(ctx, &rdroid_zeroVector3);
}

void sithCogThing_GetThingUvec(sithCog *ctx)
{
    sithThing *thing; // eax

    thing = sithCogVm_PopThing(ctx);
    if ( thing )
        sithCogVm_PushVector3(ctx, &thing->lookOrientation.uvec);
    else
        sithCogVm_PushVector3(ctx, &rdroid_zeroVector3);
}

void sithCogThing_GetThingRvec(sithCog *ctx)
{
    sithThing* thing = sithCogVm_PopThing(ctx);

    if ( thing )
        sithCogVm_PushVector3(ctx, &thing->lookOrientation.rvec);
    else
        sithCogVm_PushVector3(ctx, &rdroid_zeroVector3);
}

void sithCogThing_GetEyePYR(sithCog *ctx)
{
    sithThing* thing = sithCogVm_PopThing(ctx);

    if ( thing && (thing->thingType == THINGTYPE_ACTOR || thing->thingType == THINGTYPE_PLAYER))
        sithCogVm_PushVector3(ctx, &thing->actorParams.eyePYR);
    else
        sithCogVm_PushVector3(ctx, (rdVector3*)&rdroid_zeroVector3);
}

void sithCogThing_Initialize(void* ctx)
{
    sithCogScript_RegisterVerb(ctx, (intptr_t)sithCogThing_WaitForStop, "waitforstop");
    sithCogScript_RegisterVerb(ctx, (intptr_t)sithCogThing_StopThing, "stopthing");
    sithCogScript_RegisterVerb(ctx, (intptr_t)sithCogThing_DestroyThing, "destroything");
    sithCogScript_RegisterVerb(ctx, (intptr_t)sithCogThing_GetThingHealth, "getthinghealth");
    sithCogScript_RegisterVerb(ctx, (intptr_t)sithCogThing_GetThingHealth, "gethealth");
    sithCogScript_RegisterVerb(ctx, (intptr_t)sithCogThing_HealThing, "healthing");
    sithCogScript_RegisterVerb(ctx, (intptr_t)sithCogThing_GetThingLight, "getthinglight");
    sithCogScript_RegisterVerb(ctx, (intptr_t)sithCogThing_SetThingLight, "setthinglight");
    sithCogScript_RegisterVerb(ctx, (intptr_t)sithCogThing_SetThingLight, "thinglight");
    sithCogScript_RegisterVerb(ctx, (intptr_t)sithCogThing_ThingLightAnim, "thinglightanim");
    sithCogScript_RegisterVerb(ctx, (intptr_t)sithCogThing_Rotate, "rotate");
    sithCogScript_RegisterVerb(ctx, (intptr_t)sithCogThing_CreateThing, "creatething");
    sithCogScript_RegisterVerb(ctx, (intptr_t)sithCogThing_CreateThingNr, "createthingnr");
    sithCogScript_RegisterVerb(ctx, (intptr_t)sithCogThing_CreateThingAtPos, "createthingatpos");
    sithCogScript_RegisterVerb(ctx, (intptr_t)sithCogThing_CreateThingAtPosNr, "createthingatposnr");
    sithCogScript_RegisterVerb(ctx, (intptr_t)sithCogThing_RotatePivot, "rotatepivot");
    sithCogScript_RegisterVerb(ctx, (intptr_t)sithCogThing_CaptureThing, "capturething");
    sithCogScript_RegisterVerb(ctx, (intptr_t)sithCogThing_ReleaseThing, "releasething");
    sithCogScript_RegisterVerb(ctx, (intptr_t)sithCogThing_SetThingVel, "setthingvel");
    sithCogScript_RegisterVerb(ctx, (intptr_t)sithCogThing_AddThingVel, "addthingvel");
    sithCogScript_RegisterVerb(ctx, (intptr_t)sithCogThing_ApplyForce, "applyforce");
    sithCogScript_RegisterVerb(ctx, (intptr_t)sithCogThing_DetachThing, "detachthing");
    sithCogScript_RegisterVerb(ctx, (intptr_t)sithCogThing_GetAttachFlags, "getattachflags");
    sithCogScript_RegisterVerb(ctx, (intptr_t)sithCogThing_GetAttachFlags, "getthingattachflags");
    sithCogScript_RegisterVerb(ctx, (intptr_t)sithCogThing_AttachThingToSurf, "attachthingtosurf");
    sithCogScript_RegisterVerb(ctx, (intptr_t)sithCogThing_AttachThingToThing, "attachthingtothing");
    sithCogScript_RegisterVerb(ctx, (intptr_t)sithCogThing_SetArmedMode, "setarmedmode");
    sithCogScript_RegisterVerb(ctx, (intptr_t)sithCogThing_SetThingFlags, "setthingflags");
    sithCogScript_RegisterVerb(ctx, (intptr_t)sithCogThing_ClearThingFlags, "clearthingflags");
    sithCogScript_RegisterVerb(ctx, (intptr_t)sithCogThing_TeleportThing, "teleportthing");
    sithCogScript_RegisterVerb(ctx, (intptr_t)sithCogThing_SetThingType, "setthingtype");
    sithCogScript_RegisterVerb(ctx, (intptr_t)sithCogThing_SetCollideType, "setcollidetype");
    sithCogScript_RegisterVerb(ctx, (intptr_t)sithCogThing_SetHeadlightIntensity, "setheadlightintensity");
    sithCogScript_RegisterVerb(ctx, (intptr_t)sithCogThing_GetThingGeoMode, "getthinggeomode");
    sithCogScript_RegisterVerb(ctx, (intptr_t)sithCogThing_SetThingGeoMode, "setthinggeomode");
    sithCogScript_RegisterVerb(ctx, (intptr_t)sithCogThing_GetThingLightMode, "getthinglightmode");
    sithCogScript_RegisterVerb(ctx, (intptr_t)sithCogThing_SetThingLightMode, "setthinglightmode");
    sithCogScript_RegisterVerb(ctx, (intptr_t)sithCogThing_GetThingTexMode, "getthingtexmode");
    sithCogScript_RegisterVerb(ctx, (intptr_t)sithCogThing_SetThingTexMode, "setthingtexmode");
    sithCogScript_RegisterVerb(ctx, (intptr_t)sithCogThing_GetThingCurGeoMode, "getthingcurgeomode");
    sithCogScript_RegisterVerb(ctx, (intptr_t)sithCogThing_SetThingCurGeoMode, "setthingcurgeomode");
    sithCogScript_RegisterVerb(ctx, (intptr_t)sithCogThing_GetThingCurLightMode, "getthingcurlightmode");
    sithCogScript_RegisterVerb(ctx, (intptr_t)sithCogThing_SetThingCurLightmode, "setthingcurlightmode");
    sithCogScript_RegisterVerb(ctx, (intptr_t)sithCogThing_GetThingCurTexMode, "getthingcurtexmode");
    sithCogScript_RegisterVerb(ctx, (intptr_t)sithCogThing_SetThingCurTexMode, "setthingcurtexmode");
    sithCogScript_RegisterVerb(ctx, (intptr_t)sithCogThing_SetActorExtraSpeed, "setactorextraspeed");
    sithCogScript_RegisterVerb(ctx, (intptr_t)sithCogThing_GetThingType, "getthingtype");
    sithCogScript_RegisterVerb(ctx, (intptr_t)sithCogThing_IsMoving, "isthingmoving");
    sithCogScript_RegisterVerb(ctx, (intptr_t)sithCogThing_IsMoving, "ismoving");
    sithCogScript_RegisterVerb(ctx, (intptr_t)sithCogThing_GetCurFrame, "getcurframe");
    sithCogScript_RegisterVerb(ctx, (intptr_t)sithCogThing_GetGoalFrame, "getgoalframe");
    sithCogScript_RegisterVerb(ctx, (intptr_t)sithCogThing_GetThingParent, "getthingparent");
    sithCogScript_RegisterVerb(ctx, (intptr_t)sithCogThing_GetThingSector, "getthingsector");
    sithCogScript_RegisterVerb(ctx, (intptr_t)sithCogThing_GetThingPos, "getthingpos");
    sithCogScript_RegisterVerb(ctx, (intptr_t)sithCogThing_SetThingPos, "setthingpos");
    sithCogScript_RegisterVerb(ctx, (intptr_t)sithCogThing_GetThingVel, "getthingvel");
    sithCogScript_RegisterVerb(ctx, (intptr_t)sithCogThing_GetThingUvec, "getthinguvec");
    sithCogScript_RegisterVerb(ctx, (intptr_t)sithCogThing_GetThingLvec, "getthinglvec");
    sithCogScript_RegisterVerb(ctx, (intptr_t)sithCogThing_GetThingRvec, "getthingrvec");
    sithCogScript_RegisterVerb(ctx, (intptr_t)sithCogThing_GetThingFlags, "getthingflags");
    sithCogScript_RegisterVerb(ctx, (intptr_t)sithCogThing_GetCollideType, "getcollidetype");
    sithCogScript_RegisterVerb(ctx, (intptr_t)sithCogThing_GetHeadlightIntensity, "getheadlightintensity");
    sithCogScript_RegisterVerb(ctx, (intptr_t)sithCogThing_IsThingVisible, "isthingvisible");
    sithCogScript_RegisterVerb(ctx, (intptr_t)sithCogThing_SetThingPulse, "setthingpulse");
    sithCogScript_RegisterVerb(ctx, (intptr_t)sithCogThing_SetThingTimer, "setthingtimer");
    sithCogScript_RegisterVerb(ctx, (intptr_t)sithCogThing_GetInv, "getinv");
    sithCogScript_RegisterVerb(ctx, (intptr_t)sithCogThing_SetInv, "setinv");
    sithCogScript_RegisterVerb(ctx, (intptr_t)sithCogThing_ChangeInv, "changeinv");
    sithCogScript_RegisterVerb(ctx, (intptr_t)sithCogThing_GetInvCog, "getinvcog");
    sithCogScript_RegisterVerb(ctx, (intptr_t)sithCogThing_GetInvMin, "getinvmin");
    sithCogScript_RegisterVerb(ctx, (intptr_t)sithCogThing_GetInvMax, "getinvmax");
    sithCogScript_RegisterVerb(ctx, (intptr_t)sithCogThing_GetCurInvWeapon, "getcurinvweapon");
    sithCogScript_RegisterVerb(ctx, (intptr_t)sithCogThing_SetCurInvWeapon, "setcurinvweapon");
    sithCogScript_RegisterVerb(ctx, (intptr_t)sithCogThing_PlayKey, "playkey");
    sithCogScript_RegisterVerb(ctx, (intptr_t)sithCogThing_StopKey, "stopkey");
    sithCogScript_RegisterVerb(ctx, (intptr_t)sithCogThing_SetThingModel, "setthingmodel");
    sithCogScript_RegisterVerb(ctx, (intptr_t)sithCogThing_GetThingModel, "getthingmodel");
    sithCogScript_RegisterVerb(ctx, (intptr_t)sithCogThing_PlayMode, "playmode");
    sithCogScript_RegisterVerb(ctx, (intptr_t)sithCogThing_GetMajorMode, "getmajormode");
    sithCogScript_RegisterVerb(ctx, (intptr_t)sithCogThing_FirstThingInSector, "firstthinginsector");
    sithCogScript_RegisterVerb(ctx, (intptr_t)sithCogThing_NextThingInSector, "nextthinginsector");
    sithCogScript_RegisterVerb(ctx, (intptr_t)sithCogThing_PrevThingInSector, "prevthinginsector");
    sithCogScript_RegisterVerb(ctx, (intptr_t)sithCogThing_MoveToFrame, "movetoframe");
    sithCogScript_RegisterVerb(ctx, (intptr_t)sithCogThing_SkipToFrame, "skiptoframe");
    sithCogScript_RegisterVerb(ctx, (intptr_t)sithCogThing_JumpToFrame, "jumptoframe");
    sithCogScript_RegisterVerb(ctx, (intptr_t)sithCogThing_PathMovePause, "pathmovepause");
    sithCogScript_RegisterVerb(ctx, (intptr_t)sithCogThing_PathMoveResume, "pathmoveresume");
    sithCogScript_RegisterVerb(ctx, (intptr_t)sithCogThing_GetThingTemplate, "getthingtemplate");
    sithCogScript_RegisterVerb(ctx, (intptr_t)sithCogThing_DamageThing, "damagething");
    sithCogScript_RegisterVerb(ctx, (intptr_t)sithCogThing_SetLifeLeft, "setlifeleft");
    sithCogScript_RegisterVerb(ctx, (intptr_t)sithCogThing_GetLifeLeft, "getlifeleft");
    sithCogScript_RegisterVerb(ctx, (intptr_t)sithCogThing_SetThingThrust, "setthingthrust");
    sithCogScript_RegisterVerb(ctx, (intptr_t)sithCogThing_GetThingThrust, "getthingthrust");
    sithCogScript_RegisterVerb(ctx, (intptr_t)sithCogThing_SetHealth, "setthinghealth");
    sithCogScript_RegisterVerb(ctx, (intptr_t)sithCogThing_SetHealth, "sethealth");
    sithCogScript_RegisterVerb(ctx, (intptr_t)sithCogThing_AmputateJoint, "amputatejoint");
    sithCogScript_RegisterVerb(ctx, (intptr_t)sithCogThing_SetActorWeapon, "setactorweapon");
    sithCogScript_RegisterVerb(ctx, (intptr_t)sithCogThing_GetActorWeapon, "getactorweapon");
    sithCogScript_RegisterVerb(ctx, (intptr_t)sithCogThing_GetPhysicsFlags, "getphysicsflags");
    sithCogScript_RegisterVerb(ctx, (intptr_t)sithCogThing_SetPhysicsFlags, "setphysicsflags");
    sithCogScript_RegisterVerb(ctx, (intptr_t)sithCogThing_ClearPhysicsFlags, "clearphysicsflags");
    sithCogScript_RegisterVerb(ctx, (intptr_t)sithCogThing_SkillTarget, "skilltarget");
    sithCogScript_RegisterVerb(ctx, (intptr_t)sithCogThing_ParseArg, "parsearg");
    sithCogScript_RegisterVerb(ctx, (intptr_t)sithCogThing_GetThingRotVel, "getthingrotvel");
    sithCogScript_RegisterVerb(ctx, (intptr_t)sithCogThing_SetThingRotVel, "setthingrotvel");
    sithCogScript_RegisterVerb(ctx, (intptr_t)sithCogThing_SetThingLook, "setthinglook");
    sithCogScript_RegisterVerb(ctx, (intptr_t)sithCogThing_IsCrouching, "isthingcrouching");
    sithCogScript_RegisterVerb(ctx, (intptr_t)sithCogThing_IsCrouching, "iscrouching");
    sithCogScript_RegisterVerb(ctx, (intptr_t)sithCogThing_GetThingClassCog, "getthingclasscog");
    sithCogScript_RegisterVerb(ctx, (intptr_t)sithCogThing_SetThingClassCog, "setthingclasscog");
    sithCogScript_RegisterVerb(ctx, (intptr_t)sithCogThing_GetThingCaptureCog, "getthingcapturecog");
    sithCogScript_RegisterVerb(ctx, (intptr_t)sithCogThing_SetThingCaptureCog, "setthingcapturecog");
    sithCogScript_RegisterVerb(ctx, (intptr_t)sithCogThing_GetThingRespawn, "getthingrespawn");
    sithCogScript_RegisterVerb(ctx, (intptr_t)sithCogThing_GetThingSignature, "getthingsignature");
    sithCogScript_RegisterVerb(ctx, (intptr_t)sithCogThing_SetThingAttachFlags, "setthingattachflags");
    sithCogScript_RegisterVerb(ctx, (intptr_t)sithCogThing_ClearThingAttachFlags, "clearthingattachflags");
    sithCogScript_RegisterVerb(ctx, (intptr_t)sithCogThing_GetParticleSize, "getparticlesize");
    sithCogScript_RegisterVerb(ctx, (intptr_t)sithCogThing_SetParticleSize, "setparticlesize");
    sithCogScript_RegisterVerb(ctx, (intptr_t)sithCogThing_GetParticleGrowthSpeed, "getparticlegrowthspeed");
    sithCogScript_RegisterVerb(ctx, (intptr_t)sithCogThing_SetParticleGrowthSpeed, "setparticlegrowthspeed");
    sithCogScript_RegisterVerb(ctx, (intptr_t)sithCogThing_GetParticleTimeoutRate, "getparticletimeoutrate");
    sithCogScript_RegisterVerb(ctx, (intptr_t)sithCogThing_SetParticleTimeoutRate, "setparticletimeoutrate");
    sithCogScript_RegisterVerb(ctx, (intptr_t)sithCogThing_GetXFlags, "gettypeflags");
    sithCogScript_RegisterVerb(ctx, (intptr_t)sithCogThing_SetXFlags, "settypeflags");
    sithCogScript_RegisterVerb(ctx, (intptr_t)sithCogThing_ClearXFlags, "cleartypeflags");
    sithCogScript_RegisterVerb(ctx, (intptr_t)sithCogThing_GetXFlags, "getactorflags");
    sithCogScript_RegisterVerb(ctx, (intptr_t)sithCogThing_SetXFlags, "setactorflags");
    sithCogScript_RegisterVerb(ctx, (intptr_t)sithCogThing_ClearXFlags, "clearactorflags");
    sithCogScript_RegisterVerb(ctx, (intptr_t)sithCogThing_GetXFlags, "getweaponflags");
    sithCogScript_RegisterVerb(ctx, (intptr_t)sithCogThing_SetXFlags, "setweaponflags");
    sithCogScript_RegisterVerb(ctx, (intptr_t)sithCogThing_ClearXFlags, "clearweaponflags");
    sithCogScript_RegisterVerb(ctx, (intptr_t)sithCogThing_GetXFlags, "getexplosionflags");
    sithCogScript_RegisterVerb(ctx, (intptr_t)sithCogThing_SetXFlags, "setexplosionflags");
    sithCogScript_RegisterVerb(ctx, (intptr_t)sithCogThing_ClearXFlags, "clearexplosionflags");
    sithCogScript_RegisterVerb(ctx, (intptr_t)sithCogThing_GetXFlags, "getitemflags");
    sithCogScript_RegisterVerb(ctx, (intptr_t)sithCogThing_SetXFlags, "setitemflags");
    sithCogScript_RegisterVerb(ctx, (intptr_t)sithCogThing_ClearXFlags, "clearitemflags");
    sithCogScript_RegisterVerb(ctx, (intptr_t)sithCogThing_GetXFlags, "getparticleflags");
    sithCogScript_RegisterVerb(ctx, (intptr_t)sithCogThing_SetXFlags, "setparticleflags");
    sithCogScript_RegisterVerb(ctx, (intptr_t)sithCogThing_ClearXFlags, "clearparticleflags");
    sithCogScript_RegisterVerb(ctx, (intptr_t)sithCogThing_TakeItem, "takeitem");
    sithCogScript_RegisterVerb(ctx, (intptr_t)sithCogThing_HasLos, "haslos");
    sithCogScript_RegisterVerb(ctx, (intptr_t)sithCogThing_GetThingFireOffset, "getthingfireoffset");
    sithCogScript_RegisterVerb(ctx, (intptr_t)sithCogThing_SetThingFireOffset, "setthingfireoffset");
    sithCogScript_RegisterVerb(ctx, (intptr_t)sithCogThing_GetThingUserdata, "getthinguserdata");
    sithCogScript_RegisterVerb(ctx, (intptr_t)sithCogThing_SetThingUserdata, "setthinguserdata");
    sithCogScript_RegisterVerb(ctx, (intptr_t)sithCogThing_GetThingCollideSize, "getthingcollidesize");
    sithCogScript_RegisterVerb(ctx, (intptr_t)sithCogThing_SetThingCollideSize, "setthingcollidesize");
    sithCogScript_RegisterVerb(ctx, (intptr_t)sithCogThing_GetThingMoveSize, "getthingmovesize");
    sithCogScript_RegisterVerb(ctx, (intptr_t)sithCogThing_SetThingMoveSize, "setthingmovesize");
    sithCogScript_RegisterVerb(ctx, (intptr_t)sithCogThing_GetThingMass, "getthingmass");
    sithCogScript_RegisterVerb(ctx, (intptr_t)sithCogThing_SetThingMass, "setthingmass");
    sithCogScript_RegisterVerb(ctx, (intptr_t)sithCogThing_SyncThingPos, "syncthingpos");
    sithCogScript_RegisterVerb(ctx, (intptr_t)sithCogThing_SyncThingAttachment, "syncthingattachment");
    sithCogScript_RegisterVerb(ctx, (intptr_t)sithCogThing_SyncThingState, "syncthingstate");
    sithCogScript_RegisterVerb(ctx, (intptr_t)sithCogThing_AttachThingToThingEx, "attachthingtothingex");
}
