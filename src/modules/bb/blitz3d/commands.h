#ifndef BB_BLITZ3D_COMMANDS_H
#define BB_BLITZ3D_COMMANDS_H

#include <bb/blitz/module.h>
#include <bb/blitz3d/blitz3d.h>

#ifdef __cplusplus
extern "C" {
#endif

// AUTOGENERATED. DO NOT EDIT.
// RUN `make` TO UPDATE.
void BBCALL bbLoaderMatrix( BBStr *file_ext,bb_float_t xx,bb_float_t xy,bb_float_t xz,bb_float_t yx,bb_float_t yy,bb_float_t yz,bb_float_t zx,bb_float_t zy,bb_float_t zz );
void BBCALL bbHWMultiTex( bb_int_t enable );
bb_int_t BBCALL bbHWTexUnits(  );
bb_int_t BBCALL bbGfxDriverCaps3D(  );
void BBCALL bbWBuffer( bb_int_t enable );
void BBCALL bbDither( bb_int_t enable );
void BBCALL bbAntiAlias( bb_int_t enable );
void BBCALL bbWireFrame( bb_int_t enable );
void BBCALL bbAmbientLight( bb_float_t red,bb_float_t green,bb_float_t blue );
void BBCALL bbClearCollisions(  );
void BBCALL bbCollisions( bb_int_t source_type,bb_int_t destination_type,bb_int_t method,bb_int_t response );
void BBCALL bbUpdateWorld( bb_float_t elapsed_time );
void BBCALL bbCaptureWorld(  );
void BBCALL bbRenderWorld( bb_float_t tween );
void BBCALL bbClearWorld( bb_int_t entities,bb_int_t brushes,bb_int_t textures );
bb_int_t BBCALL bbActiveTextures(  );
bb_int_t BBCALL bbTrisRendered(  );
bb_float_t BBCALL bbStats3D( bb_int_t type );
Texture * BBCALL bbCreateTexture( bb_int_t width,bb_int_t height,bb_int_t flags,bb_int_t frames );
Texture * BBCALL bbLoadTexture( BBStr *file,bb_int_t flags );
Texture * BBCALL bbLoadAnimTexture( BBStr *file,bb_int_t flags,bb_int_t width,bb_int_t height,bb_int_t first,bb_int_t count );
void BBCALL bbFreeTexture( Texture *texture );
void BBCALL bbTextureBlend( Texture *texture,bb_int_t blend );
void BBCALL bbTextureCoords( Texture *texture,bb_int_t coords );
void BBCALL bbScaleTexture( Texture *texture,bb_float_t u_scale,bb_float_t v_scale );
void BBCALL bbRotateTexture( Texture *texture,bb_float_t angle );
void BBCALL bbPositionTexture( Texture *texture,bb_float_t u_offset,bb_float_t v_offset );
bb_int_t BBCALL bbTextureWidth( Texture *texture );
bb_int_t BBCALL bbTextureHeight( Texture *texture );
BBStr * BBCALL bbTextureName( Texture *texture );
void BBCALL bbSetCubeFace( Texture *texture,bb_int_t face );
void BBCALL bbSetCubeMode( Texture *texture,bb_int_t mode );
BBCanvas * BBCALL bbTextureBuffer( Texture *texture,bb_int_t frame );
void BBCALL bbClearTextureFilters(  );
void BBCALL bbTextureFilter( BBStr *match_text,bb_int_t texture_flags );
Brush * BBCALL bbCreateBrush( bb_float_t red,bb_float_t green,bb_float_t blue );
Brush * BBCALL bbLoadBrush( BBStr *file,bb_int_t texture_flags,bb_float_t u_scale,bb_float_t v_scale );
void BBCALL bbFreeBrush( Brush *brush );
void BBCALL bbBrushColor( Brush *brush,bb_float_t red,bb_float_t green,bb_float_t blue );
bb_int_t BBCALL bbGetBrushRed( Brush *brush );
bb_int_t BBCALL bbGetBrushGreen( Brush *brush );
bb_int_t BBCALL bbGetBrushBlue( Brush *brush );
void BBCALL bbBrushAlpha( Brush *brush,bb_float_t alpha );
bb_float_t BBCALL bbGetBrushAlpha( Brush *brush );
void BBCALL bbBrushShininess( Brush *brush,bb_float_t shininess );
bb_float_t BBCALL bbGetBrushShininess( Brush *brush );
void BBCALL bbBrushTexture( Brush *brush,Texture *texture,bb_int_t frame,bb_int_t index );
Texture * BBCALL bbGetBrushTexture( Brush *brush,bb_int_t index );
void BBCALL bbBrushBlend( Brush *brush,bb_int_t blend );
bb_int_t BBCALL bbGetBrushBlend( Brush *brush );
void BBCALL bbBrushFX( Brush *brush,bb_int_t fx );
bb_int_t BBCALL bbGetBrushFX( Brush *brush );
Entity * BBCALL bbLoadMesh( BBStr *file,Entity *parent );
Entity * BBCALL bbLoadAnimMesh( BBStr *file,Entity *parent );
bb_int_t BBCALL bbLoadAnimSeq( Object *entity,BBStr *file );
Entity * BBCALL bbCreateMesh( Entity *parent );
Entity * BBCALL bbCreateCube( Entity *parent );
Entity * BBCALL bbCreateSphere( bb_int_t segments,Entity *parent );
Entity * BBCALL bbCreateCylinder( bb_int_t segments,bb_int_t solid,Entity *parent );
Entity * BBCALL bbCreateCone( bb_int_t segments,bb_int_t solid,Entity *parent );
Entity * BBCALL bbCopyMesh( MeshModel *mesh,Entity *parent );
void BBCALL bbScaleMesh( MeshModel *mesh,bb_float_t x_scale,bb_float_t y_scale,bb_float_t z_scale );
void BBCALL bbRotateMesh( MeshModel *mesh,bb_float_t pitch,bb_float_t yaw,bb_float_t roll );
void BBCALL bbPositionMesh( MeshModel *mesh,bb_float_t x,bb_float_t y,bb_float_t z );
void BBCALL bbFitMesh( MeshModel *mesh,bb_float_t x,bb_float_t y,bb_float_t z,bb_float_t width,bb_float_t height,bb_float_t depth,bb_int_t uniform );
void BBCALL bbFlipMesh( MeshModel *mesh );
void BBCALL bbPaintMesh( MeshModel *mesh,Brush *brush );
void BBCALL bbAddMesh( MeshModel *source_mesh,MeshModel *dest_mesh );
void BBCALL bbUpdateNormals( MeshModel *mesh );
void BBCALL bbLightMesh( MeshModel *mesh,bb_float_t red,bb_float_t green,bb_float_t blue,bb_float_t range,bb_float_t x,bb_float_t y,bb_float_t z );
bb_float_t BBCALL bbMeshWidth( MeshModel *mesh );
bb_float_t BBCALL bbMeshHeight( MeshModel *mesh );
bb_float_t BBCALL bbMeshDepth( MeshModel *mesh );
bb_int_t BBCALL bbMeshesIntersect( MeshModel *mesh_a,MeshModel *mesh_b );
bb_int_t BBCALL bbCountSurfaces( MeshModel *mesh );
Surface * BBCALL bbGetSurface( MeshModel *mesh,bb_int_t surface_index );
void BBCALL bbMeshCullBox( MeshModel *mesh,bb_float_t x,bb_float_t y,bb_float_t z,bb_float_t width,bb_float_t height,bb_float_t depth );
Surface * BBCALL bbCreateSurface( MeshModel *mesh,Brush *brush );
Brush * BBCALL bbGetSurfaceBrush( Surface *surface );
Brush * BBCALL bbGetEntityBrush( Model *entity );
Surface * BBCALL bbFindSurface( MeshModel *mesh,Brush *brush );
void BBCALL bbClearSurface( Surface *surface,bb_int_t clear_vertices,bb_int_t clear_triangles );
void BBCALL bbPaintSurface( Surface *surface,Brush *brush );
bb_int_t BBCALL bbAddVertex( Surface *surface,bb_float_t x,bb_float_t y,bb_float_t z,bb_float_t u,bb_float_t v,bb_float_t w );
bb_int_t BBCALL bbAddTriangle( Surface *surface,bb_int_t v0,bb_int_t v1,bb_int_t v2 );
void BBCALL bbVertexCoords( Surface *surface,bb_int_t index,bb_float_t x,bb_float_t y,bb_float_t z );
void BBCALL bbVertexNormal( Surface *surface,bb_int_t index,bb_float_t nx,bb_float_t ny,bb_float_t nz );
void BBCALL bbVertexColor( Surface *surface,bb_int_t index,bb_float_t red,bb_float_t green,bb_float_t blue,bb_float_t alpha );
void BBCALL bbVertexTexCoords( Surface *surface,bb_int_t index,bb_float_t u,bb_float_t v,bb_float_t w,bb_int_t coord_set );
bb_int_t BBCALL bbCountVertices( Surface *surface );
bb_int_t BBCALL bbCountTriangles( Surface *surface );
bb_float_t BBCALL bbVertexX( Surface *surface,bb_int_t index );
bb_float_t BBCALL bbVertexY( Surface *surface,bb_int_t index );
bb_float_t BBCALL bbVertexZ( Surface *surface,bb_int_t index );
bb_float_t BBCALL bbVertexNX( Surface *surface,bb_int_t index );
bb_float_t BBCALL bbVertexNY( Surface *surface,bb_int_t index );
bb_float_t BBCALL bbVertexNZ( Surface *surface,bb_int_t index );
bb_float_t BBCALL bbVertexRed( Surface *surface,bb_int_t index );
bb_float_t BBCALL bbVertexGreen( Surface *surface,bb_int_t index );
bb_float_t BBCALL bbVertexBlue( Surface *surface,bb_int_t index );
bb_float_t BBCALL bbVertexAlpha( Surface *surface,bb_int_t index );
bb_float_t BBCALL bbVertexU( Surface *surface,bb_int_t index,bb_int_t coord_set );
bb_float_t BBCALL bbVertexV( Surface *surface,bb_int_t index,bb_int_t coord_set );
bb_float_t BBCALL bbVertexW( Surface *surface,bb_int_t index,bb_int_t coord_set );
bb_int_t BBCALL bbTriangleVertex( Surface *surface,bb_int_t index,bb_int_t vertex );
Entity * BBCALL bbCreateCamera( Entity *parent );
void BBCALL bbCameraZoom( Camera *camera,bb_float_t zoom );
void BBCALL bbCameraRange( Camera *camera,bb_float_t near,bb_float_t far );
void BBCALL bbCameraClsColor( Camera *camera,bb_float_t red,bb_float_t green,bb_float_t blue );
void BBCALL bbCameraClsMode( Camera *camera,bb_int_t cls_color,bb_int_t cls_zbuffer );
void BBCALL bbCameraProjMode( Camera *camera,bb_int_t mode );
void BBCALL bbCameraViewport( Camera *camera,bb_int_t x,bb_int_t y,bb_int_t width,bb_int_t height );
void BBCALL bbCameraFogColor( Camera *camera,bb_float_t red,bb_float_t green,bb_float_t blue );
void BBCALL bbCameraFogRange( Camera *camera,bb_float_t near,bb_float_t far );
void BBCALL bbCameraFogMode( Camera *camera,bb_int_t mode );
bb_int_t BBCALL bbCameraProject( Camera *camera,bb_float_t x,bb_float_t y,bb_float_t z );
bb_float_t BBCALL bbProjectedX(  );
bb_float_t BBCALL bbProjectedY(  );
bb_float_t BBCALL bbProjectedZ(  );
bb_int_t BBCALL bbEntityInView( Entity *entity,Camera *camera );
bb_int_t BBCALL bbEntityVisible( Object *src_entity,Object *dest_entity );
Entity * BBCALL bbEntityPick( Object *entity,bb_float_t range );
Entity * BBCALL bbLinePick( bb_float_t x,bb_float_t y,bb_float_t z,bb_float_t dx,bb_float_t dy,bb_float_t dz,bb_float_t radius );
Entity * BBCALL bbCameraPick( Camera *camera,bb_float_t viewport_x,bb_float_t viewport_y );
bb_float_t BBCALL bbPickedX(  );
bb_float_t BBCALL bbPickedY(  );
bb_float_t BBCALL bbPickedZ(  );
bb_float_t BBCALL bbPickedNX(  );
bb_float_t BBCALL bbPickedNY(  );
bb_float_t BBCALL bbPickedNZ(  );
bb_float_t BBCALL bbPickedTime(  );
Object * BBCALL bbPickedEntity(  );
Surface * BBCALL bbPickedSurface(  );
bb_int_t BBCALL bbPickedTriangle(  );
Entity * BBCALL bbCreateLight( bb_int_t type,Entity *parent );
void BBCALL bbLightColor( Light *light,bb_float_t red,bb_float_t green,bb_float_t blue );
void BBCALL bbLightRange( Light *light,bb_float_t range );
void BBCALL bbLightConeAngles( Light *light,bb_float_t inner_angle,bb_float_t outer_angle );
Entity * BBCALL bbCreatePivot( Entity *parent );
Entity * BBCALL bbCreateSprite( Entity *parent );
Entity * BBCALL bbLoadSprite( BBStr *file,bb_int_t texture_flags,Entity *parent );
void BBCALL bbRotateSprite( Sprite *sprite,bb_float_t angle );
void BBCALL bbScaleSprite( Sprite *sprite,bb_float_t x_scale,bb_float_t y_scale );
void BBCALL bbHandleSprite( Sprite *sprite,bb_float_t x_handle,bb_float_t y_handle );
void BBCALL bbSpriteViewMode( Sprite *sprite,bb_int_t view_mode );
Entity * BBCALL bbLoadMD2( BBStr *file,Entity *parent );
void BBCALL bbAnimateMD2( MD2Model *md2,bb_int_t mode,bb_float_t speed,bb_int_t first_frame,bb_int_t last_frame,bb_float_t transition );
bb_float_t BBCALL bbMD2AnimTime( MD2Model *md2 );
bb_int_t BBCALL bbMD2AnimLength( MD2Model *md2 );
bb_int_t BBCALL bbMD2Animating( MD2Model *md2 );
Entity * BBCALL bbLoadBSP( BBStr *file,bb_float_t gamma_adj,Entity *parent );
void BBCALL bbBSPLighting( Q3BSPModel *bsp,bb_int_t use_lightmaps );
void BBCALL bbBSPAmbientLight( Q3BSPModel *bsp,bb_float_t red,bb_float_t green,bb_float_t blue );
Entity * BBCALL bbCreateMirror( Entity *parent );
Entity * BBCALL bbCreatePlane( bb_int_t segments,Entity *parent );
Entity * BBCALL bbCreateTerrain( bb_int_t grid_size,Entity *parent );
Entity * BBCALL bbLoadTerrain( BBStr *heightmap_file,Entity *parent );
void BBCALL bbTerrainDetail( Terrain *terrain,bb_int_t detail_level,bb_int_t morph );
void BBCALL bbTerrainShading( Terrain *terrain,bb_int_t enable );
bb_float_t BBCALL bbTerrainX( Terrain *terrain,bb_float_t world_x,bb_float_t world_y,bb_float_t world_z );
bb_float_t BBCALL bbTerrainY( Terrain *terrain,bb_float_t world_x,bb_float_t world_y,bb_float_t world_z );
bb_float_t BBCALL bbTerrainZ( Terrain *terrain,bb_float_t world_x,bb_float_t world_y,bb_float_t world_z );
bb_int_t BBCALL bbTerrainSize( Terrain *terrain );
bb_float_t BBCALL bbTerrainHeight( Terrain *terrain,bb_int_t terrain_x,bb_int_t terrain_z );
void BBCALL bbModifyTerrain( Terrain *terrain,bb_int_t terrain_x,bb_int_t terrain_z,bb_float_t height,bb_int_t realtime );
Entity * BBCALL bbCreateListener( Entity *parent,bb_float_t rolloff_factor,bb_float_t doppler_scale,bb_float_t distance_scale );
BBChannel * BBCALL bbEmitSound( BBSound *sound,Object *entity );
Entity * BBCALL bbCopyEntity( Entity *entity,Entity *parent );
bb_float_t BBCALL bbEntityX( Entity *entity,bb_int_t global );
bb_float_t BBCALL bbEntityY( Entity *entity,bb_int_t global );
bb_float_t BBCALL bbEntityZ( Entity *entity,bb_int_t global );
bb_float_t BBCALL bbEntityPitch( Entity *entity,bb_int_t global );
bb_float_t BBCALL bbEntityYaw( Entity *entity,bb_int_t global );
bb_float_t BBCALL bbEntityRoll( Entity *entity,bb_int_t global );
bb_float_t BBCALL bbGetMatElement( Entity *entity,bb_int_t row,bb_int_t column );
void BBCALL bbTFormPoint( bb_float_t x,bb_float_t y,bb_float_t z,Entity *source_entity,Entity *dest_entity );
void BBCALL bbTFormVector( bb_float_t x,bb_float_t y,bb_float_t z,Entity *source_entity,Entity *dest_entity );
void BBCALL bbTFormNormal( bb_float_t x,bb_float_t y,bb_float_t z,Entity *source_entity,Entity *dest_entity );
bb_float_t BBCALL bbTFormedX(  );
bb_float_t BBCALL bbTFormedY(  );
bb_float_t BBCALL bbTFormedZ(  );
bb_float_t BBCALL bbVectorYaw( bb_float_t x,bb_float_t y,bb_float_t z );
bb_float_t BBCALL bbVectorPitch( bb_float_t x,bb_float_t y,bb_float_t z );
bb_float_t BBCALL bbDeltaPitch( Entity *src_entity,Entity *dest_entity );
bb_float_t BBCALL bbDeltaYaw( Entity *src_entity,Entity *dest_entity );
void BBCALL bbResetEntity( Object *entity );
void BBCALL bbEntityType( Object *entity,bb_int_t collision_type,bb_int_t recursive );
void BBCALL bbEntityPickMode( Object *entity,bb_int_t pick_geometry,bb_int_t obscurer );
Entity * BBCALL bbGetParent( Entity *entity );
bb_int_t BBCALL bbGetEntityType( Object *entity );
void BBCALL bbEntityRadius( Object *entity,bb_float_t x_radius,bb_float_t y_radius );
void BBCALL bbEntityBox( Object *entity,bb_float_t x,bb_float_t y,bb_float_t z,bb_float_t width,bb_float_t height,bb_float_t depth );
bb_float_t BBCALL bbEntityDistance( Entity *source_entity,Entity *destination_entity );
Object * BBCALL bbEntityCollided( Object *entity,bb_int_t type );
bb_int_t BBCALL bbCountCollisions( Object *entity );
bb_float_t BBCALL bbCollisionX( Object *entity,bb_int_t collision_index );
bb_float_t BBCALL bbCollisionY( Object *entity,bb_int_t collision_index );
bb_float_t BBCALL bbCollisionZ( Object *entity,bb_int_t collision_index );
bb_float_t BBCALL bbCollisionNX( Object *entity,bb_int_t collision_index );
bb_float_t BBCALL bbCollisionNY( Object *entity,bb_int_t collision_index );
bb_float_t BBCALL bbCollisionNZ( Object *entity,bb_int_t collision_index );
bb_float_t BBCALL bbCollisionTime( Object *entity,bb_int_t collision_index );
Object * BBCALL bbCollisionEntity( Object *entity,bb_int_t collision_index );
Surface * BBCALL bbCollisionSurface( Object *entity,bb_int_t collision_index );
bb_int_t BBCALL bbCollisionTriangle( Object *entity,bb_int_t collision_index );
void BBCALL bbMoveEntity( Entity *entity,bb_float_t x,bb_float_t y,bb_float_t z );
void BBCALL bbTurnEntity( Entity *entity,bb_float_t pitch,bb_float_t yaw,bb_float_t roll,bb_int_t global );
void BBCALL bbTranslateEntity( Entity *entity,bb_float_t x,bb_float_t y,bb_float_t z,bb_int_t global );
void BBCALL bbPositionEntity( Entity *entity,bb_float_t x,bb_float_t y,bb_float_t z,bb_int_t global );
void BBCALL bbScaleEntity( Entity *entity,bb_float_t x_scale,bb_float_t y_scale,bb_float_t z_scale,bb_int_t global );
void BBCALL bbRotateEntity( Entity *entity,bb_float_t pitch,bb_float_t yaw,bb_float_t roll,bb_int_t global );
void BBCALL bbPointEntity( Entity *entity,Entity *target,bb_float_t roll );
void BBCALL bbAlignToVector( Entity *entity,bb_float_t vector_x,bb_float_t vector_y,bb_float_t vector_z,bb_int_t axis,bb_float_t rate );
void BBCALL bbSetAnimTime( Object *entity,bb_float_t time,bb_int_t anim_seq );
void BBCALL bbAnimate( Object *entity,bb_int_t mode,bb_float_t speed,bb_int_t sequence,bb_float_t transition );
void BBCALL bbSetAnimKey( Object *entity,bb_int_t frame,bb_int_t pos_key,bb_int_t rot_key,bb_int_t scale_key );
bb_int_t BBCALL bbAddAnimSeq( Object *entity,bb_int_t length );
bb_int_t BBCALL bbExtractAnimSeq( Object *entity,bb_int_t first_frame,bb_int_t last_frame,bb_int_t anim_seq );
bb_int_t BBCALL bbAnimSeq( Object *entity );
bb_float_t BBCALL bbAnimTime( Object *entity );
bb_int_t BBCALL bbAnimLength( Object *entity );
bb_int_t BBCALL bbAnimating( Object *entity );
void BBCALL bbEntityParent( Entity *entity,Entity *parent,bb_int_t global );
bb_int_t BBCALL bbCountChildren( Entity *entity );
Entity * BBCALL bbGetChild( Entity *entity,bb_int_t index );
Entity * BBCALL bbFindChild( Entity *entity,BBStr *name );
void BBCALL bbPaintEntity( Model *entity,Brush *brush );
void BBCALL bbEntityColor( Model *entity,bb_float_t red,bb_float_t green,bb_float_t blue );
void BBCALL bbEntityAlpha( Model *entity,bb_float_t alpha );
void BBCALL bbEntityShininess( Model *entity,bb_float_t shininess );
void BBCALL bbEntityTexture( Model *entity,Texture *texture,bb_int_t frame,bb_int_t index );
void BBCALL bbEntityBlend( Model *entity,bb_int_t blend );
void BBCALL bbEntityFX( Model *entity,bb_int_t fx );
void BBCALL bbEntityAutoFade( Model *entity,bb_float_t near,bb_float_t far );
void BBCALL bbEntityOrder( Object *entity,bb_int_t order );
void BBCALL bbHideEntity( Entity *entity );
void BBCALL bbShowEntity( Entity *entity );
void BBCALL bbFreeEntity( Entity *entity );
void BBCALL bbNameEntity( Entity *entity,BBStr *name );
BBStr * BBCALL bbEntityName( Entity *entity );
BBStr * BBCALL bbEntityClass( Entity *entity );

#ifdef __cplusplus
}
#endif


#endif
