# ModelGeometryInfo-SAMP

The purpose of this script if to get some basic information of game models geometry on server. You can get similiar functions at https://github.com/Crayder/Model-Sizes-Plus - that script based on collision data of models. Here presented data that found in visual models (from \*.dff files), but it is also can be easily extended for additional data.


## Attention
There a list of main data differences presented here in front of Model-Sizes-Plus.
> * __You have to manually load desired resources.__ See 'resources' directory.
> * Here represented AABB3 for models that didn't have collision.
> * Some models like trees, bushes, flowers are bigger here because of non-collision part of model.
> * Some objects like buildings and roads have flaps that makes AABB3 bigger (avoidance method of see-though corners).
> * Some objects have too different collision than visual model.

## Functions

__ModelGeom_initVisual_AABB3(const filepath\[\])__
> Load information about visible part of objects (AABB3) from binary file.

__ModelGeom_getVisualBoxBounds(const modelid, &Float:min_x, &Float:min_y, &Float:min_z, &Float:max_x, &Float:max_y, &Float:max_z)__
> Get bounds as AABB3 of visible object.


__ModelGeom_getVisualBoxSize(const modelid, &Float:size_x, &Float:size_y, &Float:size_z)__
> Get size of AABB3 of visible object.
	

__ModelGeom_getVisualCenter(const modelid, &Float:pos_x, &Float:pos_y, &Float:pos_z)__
> Get center position of AABB3 of visible object.
