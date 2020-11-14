#include "rdMaterial.h"

#include "Engine/rdroid.h"
#include "Win95/stdDisplay.h"
#include "Win95/std.h"
#include "stdPlatform.h"
#include "jk.h"

void rdMaterial_RegisterLoader(rdMaterialLoader_t load)
{
    pMaterialsLoader = load;
}

void rdMaterial_RegisterUnloader(rdMaterialUnloader_t unload)
{
    pMaterialsUnloader = unload;
}

rdMaterial* rdMaterial_Load(char *material_fname, int create_ddraw_surface, int gpu_memory)
{
    rdMaterial *material;
    unsigned int v5;
    void **v6;
    int *v7;
    unsigned int v8;
    stdVBuffer **v9;
    unsigned int gpu_mem;

    if (pMaterialsLoader)
        return (rdMaterial*)pMaterialsLoader(material_fname, create_ddraw_surface, gpu_memory);

    material = (rdMaterial*)rdroid_pHS->alloc(sizeof(rdMaterial));
    if (material && rdMaterial_LoadEntry(material_fname, material, create_ddraw_surface, gpu_memory))
        return material;

    rdMaterial_Free(material);

    return NULL;
}

int rdMaterial_LoadEntry(char *mat_fpath, rdMaterial *material, int create_ddraw_surface, int gpu_mem)
{
  rdMaterial *material_; // ebp
  int mat_file; // eax
  int mat_file_; // ebx
  int num_texinfo; // eax
  int tex_type; // edx
  int *texture_idk; // edi
  rdTexinfo **texinfo; // esi
  rdTexinfo *texinfo_alloc; // eax
  int num_textures; // ecx
  rdTexture *textures; // eax
  int v14; // esi
  rdTexture *texture; // esi
  unsigned int mipmap_num; // ebx
  int bpp; // eax
  stdVBuffer **texture_struct; // edi
  void *v19; // ebp
  int v21; // cf
  unsigned int v22; // edi
  int *v23; // esi
  rdTexinfo **v24; // ebx
  rdColor24 *colors; // eax
  char *v26; // eax
  struct common_functions *v27; // eax
  int mat_file__; // [esp+10h] [ebp-128h]
  int tex_num; // [esp+14h] [ebp-124h]
  int tex_numa; // [esp+14h] [ebp-124h]
  int v31; // [esp+18h] [ebp-120h]
  rdTextureHeader tex_header_1; // [esp+20h] [ebp-118h]
  rdTexinfoHeader texinfo_header; // [esp+38h] [ebp-100h]
  rdTexinfoExtHeader tex_ext; // [esp+50h] [ebp-E8h]
  texture_format format; // [esp+60h] [ebp-D8h]
  rdMaterialHeader mat_header; // [esp+ACh] [ebp-8Ch]
  int textures_idk[8]; // [esp+F8h] [ebp-40h]
  stdVBuffer *created_tex; // eax

  material_ = material;
  _memset(material, 0, sizeof(rdMaterial));
  mat_file = rdroid_pHS->fileOpen(mat_fpath, "rb");
  mat_file_ = mat_file;
  mat_file__ = mat_file;
  if ( mat_file )
  {
    rdroid_pHS->fileRead(mat_file, &mat_header, 0x4C);
    if ( _memcmp(mat_header.magic, "MAT ", 4u) || mat_header.revision != '2' )
      goto LABEL_32;
    num_texinfo = mat_header.num_texinfo;
    tex_type = mat_header.type;
    material->num_textures = mat_header.num_textures;
    material->tex_type = tex_type;
    material->num_texinfo = num_texinfo;
    material->celIdx = 0;
    tex_num = 0;
    _memcpy(&material->tex_format, &mat_header.tex_format, sizeof(material->tex_format));
    if ( num_texinfo )
    {
      texture_idk = textures_idk;
      texinfo = material->texinfos;
      do
      {
        texinfo_alloc = (rdTexinfo *)rdroid_pHS->alloc(0x20u);
        *texinfo = texinfo_alloc;
        if ( !texinfo_alloc )
          goto LABEL_32;
        rdroid_pHS->fileRead(mat_file_, &texinfo_header, sizeof(rdTexinfoHeader));
        (*texinfo)->header = texinfo_header;
        if ( texinfo_header.texture_type & 8 )  // bitflag for texture, not color
        {
          rdroid_pHS->fileRead(mat_file_, &tex_ext, 0x10);
          (*texinfo)->texext_unk00 = tex_ext.unk_00;
          *texture_idk = tex_ext.unk_0c;
        }
        ++texinfo;
        ++texture_idk;
      }
      while ( (unsigned int)++tex_num < material->num_texinfo );
    }
    num_textures = material->num_textures;
    material->textures = 0;
    if ( num_textures )
    {
      textures = (rdTexture *)rdroid_pHS->alloc(sizeof(rdTexture) * num_textures);
      material->textures = textures;
      if ( !textures )
      {
LABEL_32:
        rdroid_pHS->fileClose(mat_file_);
        return 0;
      }
    }
    v14 = 0;
    tex_numa = 0;
    if ( material->num_textures )
    {
      v31 = 0;
      while ( 1 )
      {
        rdroid_pHS->fileRead(mat_file_, &tex_header_1, sizeof(rdTextureHeader));
        texture = (rdTexture *)((char *)material_->textures + v14);
        texture->alpha_en = tex_header_1.alpha_en;
        texture->unk_0c = tex_header_1.unk_0c;
        texture->width_bitcnt = stdCalcBitPos(tex_header_1.width);
        texture->width_minus_1 = tex_header_1.width - 1;
        mipmap_num = 0;
        texture->height_minus_1 = tex_header_1.height - 1;
        texture->num_mipmaps = tex_header_1.num_mipmaps;
        texture->color_transparent = tex_header_1.unk_10;
        format.width = tex_header_1.width;
        format.height = tex_header_1.height;
        bpp = material_->tex_format.bpp;
        format.format.is16bit = material->tex_format.is16bit;
        format.format.bpp = bpp;
        if ( texture->num_mipmaps )
          break;
LABEL_21:
        mat_file_ = mat_file__;
        v14 = v31 + sizeof(rdTexture);
        v21 = (unsigned int)(tex_numa++ + 1) < material_->num_textures;
        v31 += sizeof(rdTexture);
        if ( !v21 )
          goto LABEL_22;
      }
      texture_struct = (stdVBuffer **)texture->texture_struct;
      v19 = (void*)&texture->field_A4[0].surface_desc + 0xC;//.dwWidth;
      while ( 1 )
      {
        *((uint32_t *)v19 - 5) = 0;
        *(uint32_t *)v19 = 0;
        *((uint32_t *)v19 + 147) = 0;
        *((uint32_t *)v19 + 152) = 0;
        created_tex = stdDisplay_VBufferNew(&format, create_ddraw_surface, gpu_mem, 0);
        *texture_struct = created_tex;
        if ( !created_tex )
          break;
        if ( texture->alpha_en & 1 )
          stdDisplay_VBufferSetColorKey(created_tex, texture->color_transparent);
        stdDisplay_VBufferLock(*texture_struct);
        rdroid_pHS->fileRead(
          mat_file__,
          (void *)(*texture_struct)->surface_lock_alloc,
          (*texture_struct)->format.texture_size_in_bytes);
        stdDisplay_VBufferUnlock(*texture_struct);
        format.width = (unsigned int)format.width >> 1;
        format.height = (unsigned int)format.height >> 1;
        ++mipmap_num;
        ++texture_struct;
        v19 = (char *)v19 + 0x98;
        if ( mipmap_num >= texture->num_mipmaps )
        {
          material_ = material;
          goto LABEL_21;
        }
      }
      mat_file_ = mat_file__;
      goto LABEL_32;
    }
LABEL_22:
    v22 = 0;
    if ( material_->num_texinfo )
    {
      v23 = textures_idk;
      v24 = material_->texinfos;
      do
      {
        if ( (*v24)->header.texture_type & 8 )
          (*v24)->texture_ptr = &material_->textures[*v23];
        ++v22;
        ++v23;
        ++v24;
      }
      while ( v22 < material_->num_texinfo );
      mat_file_ = mat_file__;
    }
    if ( material_->tex_type & 1 )
    {
      colors = (rdColor24 *)rdroid_pHS->alloc(0x300u);
      material_->palette_alloc = colors;
      if ( !colors )
      {
        rdroid_pHS->fileClose(mat_file_);
        return 0;
      }
      rdroid_pHS->fileRead(mat_file_, colors, 0x300);
    }
    v26 = stdFileFromPath(mat_fpath);
    _strncpy(material_->mat_fpath, v26, 0x1Fu);
    v27 = rdroid_pHS;
    material_->mat_fpath[31] = 0;
    v27->fileClose(mat_file_);
    mat_file = 1;
  }
  return mat_file;
}

void rdMaterial_Free(rdMaterial *material)
{
    if (!material)
        return;

    if (pMaterialsUnloader)
    {
        pMaterialsUnloader(material);
        return;
    }

    rdMaterial_FreeEntry(material);

    rdroid_pHS->free(material);
}

void rdMaterial_FreeEntry(rdMaterial* material)
{
    unsigned int v5;
    void **v6;
    int *v7;
    unsigned int v8;
    stdVBuffer **v9;
    unsigned int gpu_mem;

    v5 = 0;
    if (material->num_texinfo)
    {
      v6 = (void **)material->texinfos;
      do
      {
        rdroid_pHS->free(*v6);
        ++v5;
        ++v6;
      }
      while ( v5 < material->num_texinfo );
    }
    gpu_mem = 0;
    if ( material->num_textures )
    {
      v7 = &material->textures->num_mipmaps;
      do
      {
        v8 = 0;
        if ( *v7 )
        {
          v9 = (stdVBuffer **)(v7 + 1);
          do
          {
            stdDisplay_free_texture(*v9);
            ++v8;
            ++v9;
          }
          while ( v8 < *v7 );
        }
        v7 += 315;
        ++gpu_mem;
      }
      while ( gpu_mem < material->num_textures );
    }

    if (material->textures)
      rdroid_pHS->free(material->textures);

    if (material->tex_type & 1)
      rdroid_pHS->free(material->palette_alloc);
}
