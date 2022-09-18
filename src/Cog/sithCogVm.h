#ifndef _SITHCOGVM_H
#define _SITHCOGVM_H

#include "types.h"
#include "globals.h"
#include "Engine/rdKeyframe.h"
#include "Cog/sithCogScript.h"
#include "World/sithThing.h"
#include "Engine/rdMaterial.h"


#define sithCogVm_Exec_ADDR (0x004E1F60)
#define sithCogVm_ExecCog_ADDR (0x004E2350)
#define sithCogVm_PopValue_ADDR (0x004E2440)
#define sithCogVm_PopFlex_ADDR (0x004E24F0)
#define sithCogVm_PopInt_ADDR (0x004E25C0)
#define sithCogVm_PopSymbolIdx_ADDR (0x004E2690)
#define sithCogVm_PopVector3_ADDR (0x004E26E0)
#define sithCogVm_PopCog_ADDR (0x004E27B0)
#define sithCogVm_PopThing_ADDR (0x004E28C0)
#define sithCogVm_PopTemplate_ADDR (0x004E29C0)
#define sithCogVm_PopSound_ADDR (0x004E2AD0)
#define sithCogVm_PopSector_ADDR (0x004E2BD0)
#define sithCogVm_PopSurface_ADDR (0x004E2CC0)
#define sithCogVm_PopMaterial_ADDR (0x004E2DB0)
#define sithCogVm_PopModel3_ADDR (0x004E2EB0)
#define sithCogVm_PopKeyframe_ADDR (0x004E2FB0)
#define sithCogVm_PopAIClass_ADDR (0x004E30B0)
#define sithCogVm_PopSymbolFunc_ADDR (0x004E31B0)
#define sithCogVm_PopString_ADDR (0x004E3260)

#define sithCogVm_PushVar_ADDR (0x004E32D0)
#define sithCogVm_PushInt_ADDR (0x004E3340)
#define sithCogVm_PushFlex_ADDR (0x004E33C0)
#define sithCogVm_PushVector3_ADDR (0x004E3450)
#define sithCogVm_PopProgramVal_ADDR (0x004E34E0)
#define sithCogVm_ResetStack_ADDR (0x004E3510)
#define sithCogVm_Call_ADDR (0x004E3530)
#define sithCogVm_Ret_ADDR (0x004E3590)
#define sithCogVm_PopStackVar_ADDR (0x004E35E0)
#define sithCogVm_BitOperation_ADDR (0x004E3630)
#define sithCogVm_MathOperation_ADDR (0x004E3870)
#define sithCogVm_AssignStackVar_ADDR (0x004E3B90)

enum SENDERTYPE
{
    SENDERTYPE_0     = 0,
    SENDERTYPE_SYSTEM  = 1,
    SENDERTYPE_2     = 2,
    SENDERTYPE_THING  = 3,
    SENDERTYPE_4     = 4,
    SENDERTYPE_SECTOR  = 5,
    SENDERTYPE_SURFACE  = 6,
    SENDERTYPE_7     = 7,
    SENDERTYPE_8     = 8,
    SENDERTYPE_COG   = 9
};

enum COG_TYPE
{
    COG_TYPE_VERB    = 0,
    COG_TYPE_1       = 1,
    COG_TYPE_FLEX  = 2,
    COG_TYPE_INT  = 3,
    COG_TYPE_TEMPLATE = 4,
    COG_TYPE_KEYFRAME = 7,
    COG_TYPE_SOUND = 8,
    COG_TYPE_MATERIAL = 10,
    COG_TYPE_VECTOR = 11,
    COG_TYPE_MODEL = 12,
    COG_TYPE_AICLASS = 13,
};

enum COG_VARTYPE
{
    COG_VARTYPE_VERB  = 0,
    COG_VARTYPE_SYMBOL  = 1,
    COG_VARTYPE_FLEX  = 2,
    COG_VARTYPE_INT  = 3,
    COG_VARTYPE_STR  = 4,
    COG_VARTYPE_VECTOR  = 5
};

enum COG_OPCODE
{
    COG_OPCODE_NOP   = 0,
    COG_OPCODE_PUSHINT  = 1,
    COG_OPCODE_PUSHFLOAT  = 2,
    COG_OPCODE_PUSHSYMBOL  = 3,
    COG_OPCODE_ARRAYINDEX  = 4,
    COG_OPCODE_CALLFUNC  = 5,
    COG_OPCODE_ASSIGN  = 6,
    COG_OPCODE_PUSHVECTOR  = 7,
    COG_OPCODE_ADD   = 8,
    COG_OPCODE_SUB   = 9,
    COG_OPCODE_MUL   = 10,
    COG_OPCODE_DIV   = 11,
    COG_OPCODE_MOD   = 12,
    COG_OPCODE_CMPFALSE  = 13,
    COG_OPCODE_NEG   = 14,
    COG_OPCODE_CMPGT  = 15,
    COG_OPCODE_CMPLS  = 16,
    COG_OPCODE_CMPEQ  = 17,
    COG_OPCODE_CMPLE  = 18,
    COG_OPCODE_CMPGE  = 19,
    COG_OPCODE_CMPAND  = 20,
    COG_OPCODE_CMPOR  = 21,
    COG_OPCODE_CMPNE  = 22,
    COG_OPCODE_ANDI  = 23,
    COG_OPCODE_ORI   = 24,
    COG_OPCODE_XORI  = 25,
    COG_OPCODE_GOFALSE  = 26,
    COG_OPCODE_GOTRUE  = 27,
    COG_OPCODE_GO    = 28,
    COG_OPCODE_RET   = 29,
    COG_OPCODE_UNK30  = 30,
    COG_OPCODE_CALL  = 31
};

void sithCogVm_Exec(sithCog *cog_ctx);
void sithCogVm_ExecCog(sithCog *ctx, int trigIdx);
int sithCogVm_PopValue(sithCog *ctx, sithCogStackvar *stackVar);
float sithCogVm_PopFlex(sithCog *ctx);
int sithCogVm_PopInt(sithCog *ctx);
int sithCogVm_PopSymbolIdx(sithCog *ctx);
int sithCogVm_PopVector3(sithCog *ctx, rdVector3* out);
sithCog* sithCogVm_PopCog(sithCog *ctx);
sithThing* sithCogVm_PopThing(sithCog *ctx);
sithThing* sithCogVm_PopTemplate(sithCog *ctx);
sithSound* sithCogVm_PopSound(sithCog *ctx);
sithSector* sithCogVm_PopSector(sithCog *ctx);
sithSurface* sithCogVm_PopSurface(sithCog *ctx);
rdMaterial* sithCogVm_PopMaterial(sithCog *ctx);
rdModel3* sithCogVm_PopModel3(sithCog *ctx);
rdKeyframe* sithCogVm_PopKeyframe(sithCog *ctx);
sithAIClass* sithCogVm_PopAIClass(sithCog *ctx);
char* sithCogVm_PopString(sithCog *ctx);
cogSymbolFunc_t sithCogVm_PopSymbolFunc(sithCog *cog_ctx);
void sithCogVm_PushVar(sithCog *ctx, sithCogStackvar *val);
void sithCogVm_PushInt(sithCog *ctx, int val);
void sithCogVm_PushFlex(sithCog *ctx, float val);
void sithCogVm_PushVector3(sithCog *ctx, const rdVector3* val);
int sithCogVm_PopProgramVal(sithCog *ctx);
void sithCogVm_ResetStack(sithCog *ctx);
void sithCogVm_Call(sithCog *ctx);
void sithCogVm_Ret(sithCog *cog_ctx);
int sithCogVm_PopStackVar(sithCog *cog, sithCogStackvar *out);
void sithCogVm_BitOperation(sithCog *cog_ctx, int op);
void sithCogVm_MathOperation(sithCog *cog_ctx, int op);
sithCogStackvar* sithCogVm_AssignStackVar(sithCogStackvar *out, sithCog *ctx, sithCogStackvar *in);

//static void (__cdecl *sithCogVm_Ret)(sithCog *cog) = (void*)sithCogVm_Ret_ADDR;
//static void (__cdecl *sithCogVm_Call)(sithCog *cog) = (void*)sithCogVm_Call_ADDR;

//static int (__cdecl *sithCogVm_PopProgramVal)(sithCog *cog) = (void*)sithCogVm_PopProgramVal_ADDR;
//static int (__cdecl *sithCogVm_PopStackVar)(sithCog *cog, sithCogStackvar *out) = (void*)sithCogVm_PopStackVar_ADDR;
//static sithCogStackvar* (__cdecl *sithCogVm_AssignStackVar)(sithCogStackvar *a1, sithCog* a2, sithCogStackvar *a3) = (void*)sithCogVm_AssignStackVar_ADDR;
//static void (__cdecl *sithCogVm_MathOperation)(sithCog *cog, int op) = (void*)sithCogVm_MathOperation_ADDR;
//static void (__cdecl *sithCogVm_BitOperation)(sithCog *cog, int op) = (void*)sithCogVm_BitOperation_ADDR;
//static int (__cdecl *sithCogVm_PopValue)(sithCog *ctx, int *out) = (void*)sithCogVm_PopValue_ADDR;
//static float (__cdecl *sithCogVm_PopFlex)(sithCog *ctx) = (void*)sithCogVm_PopFlex_ADDR;
//static int (__cdecl *sithCogVm_PopInt)(sithCog *ctx) = (void*)sithCogVm_PopInt_ADDR;
//static int (__cdecl *sithCogVm_PopVector3)(sithCog *ctx, rdVector3* out) = (void*)sithCogVm_PopVector3_ADDR;
//static char* (__cdecl *sithCogVm_PopString)(sithCog *ctx) = (void*)sithCogVm_PopString_ADDR;
//static sithSurface* (__cdecl *sithCogVm_PopSurface)(sithCog* ctx) = (void*)sithCogVm_PopSurface_ADDR;
//static void* (__cdecl *sithCogVm_PopMaterial)(sithCog* ctx) = (void*)sithCogVm_PopMaterial_ADDR;
//static rdKeyframe* (__cdecl *sithCogVm_PopKeyframe_)(sithCog* ctx) = (void*)sithCogVm_PopKeyframe_ADDR;
//static sithCog* (__cdecl *sithCogVm_PopCog)(sithCog* ctx) = (void*)sithCogVm_PopCog_ADDR;
//static int (__cdecl *sithCogVm_PopSymbolIdx)(sithCog *ctx) = (void*)sithCogVm_PopSymbolIdx_ADDR;
//static cogSymbolFunc_t (__cdecl *sithCogVm_PopSymbolFunc)(sithCog *cog_ctx) = (void*)sithCogVm_PopSymbolFunc_ADDR;

//static void (__cdecl *sithCogVm_PushVar)(sithCog *ctx, sithCogStackvar *val) = (void*)sithCogVm_PushVar_ADDR;
//static void (__cdecl *sithCogVm_PushInt)(sithCog *ctx, int val) = (void*)sithCogVm_PushInt_ADDR;
//static void (__cdecl *sithCogVm_PushFlex)(sithCog *ctx, float val) = (void*)sithCogVm_PushFlex_ADDR;
//static void (__cdecl *sithCogVm_PushVector3)(sithCog *ctx, const rdVector3 *val) = (void*)sithCogVm_PushVector3_ADDR;


#endif // _SITHCOGVM_H
