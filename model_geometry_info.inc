#if !defined __MODELGEOMETRY_INCLUDED__
#define __MODELGEOMETRY_INCLUDED__
#define MODELGEOMETRY_MODELS		(20000)
//	AABB3 - Axis Aligned Bounding Box in 3 dimensions.
//	Visual - in function name stands for information about visible model.
//	Col - in function name stands for information about collision model.

enum e_modelsize_aabb3_info {
	Float:E_MIN_X,
	Float:E_MIN_Y,
	Float:E_MIN_Z,
	Float:E_MAX_X,
	Float:E_MAX_Y,
	Float:E_MAX_Z,
};

enum e_modelsize_aabb3_line {
	E_MODELID,
	Float:E_MIN_X,
	Float:E_MIN_Y,
	Float:E_MIN_Z,
	Float:E_MAX_X,
	Float:E_MAX_Y,
	Float:E_MAX_Z,
};
static stock ModelVisual_AABB3[MODELGEOMETRY_MODELS][e_modelsize_aabb3_info];

// Load information about visible part of objects (AABB3).
stock ModelGeom_initVisual_AABB3(const filepath[]) {
	new File:f = fopen(filepath, io_read),
		line_info[e_modelsize_aabb3_line],
		modelid
	;
	if( f ) {
		while( fblockread(f, line_info, sizeof(line_info)) == sizeof(line_info) ) {
			modelid = line_info[E_MODELID];
			if( modelid > 0 && modelid < MODELGEOMETRY_MODELS ) {
				memcpy(ModelVisual_AABB3[modelid], line_info[e_modelsize_aabb3_line:1], 0, 4 * sizeof(line_info), sizeof(line_info));
			}
		}
		fclose(f);
	} else {
		printf("ModelSize_init: cant load from (%s).", filepath);
	}
}

stock ModelGeom_parseBoxBounds(
	const aabb_info[e_modelsize_aabb3_info],
	&Float:min_x,
	&Float:min_y,
	&Float:min_z,
	&Float:max_x,
	&Float:max_y,
	&Float:max_z
) {
	min_x = aabb_info[E_MIN_X];
	min_y = aabb_info[E_MIN_Y];
	min_z = aabb_info[E_MIN_Z];
	max_x = aabb_info[E_MAX_X];
	max_y = aabb_info[E_MAX_Y];
	max_z = aabb_info[E_MAX_Z];
}

//	Get bounds as AABB3 of visible object.
stock ModelGeom_getVisualBoxBounds(
	const modelid,
	&Float:min_x,
	&Float:min_y,
	&Float:min_z,
	&Float:max_x,
	&Float:max_y,
	&Float:max_z
) {
	if( modelid > 0 && modelid < MODELGEOMETRY_MODELS ) {
		ModelGeom_parseBoxBounds(ModelVisual_AABB3[modelid], min_x, min_y, min_z, max_x, max_y, max_z);
	} else {
		min_x = min_y = min_z = max_x = max_y = max_z = 0.0;
	}
}

//	Get size of AABB3 of visible object.
stock ModelGeom_getVisualBoxSize(
	const modelid,
	&Float:size_x,
	&Float:size_y,
	&Float:size_z
) {
	new Float:min_x, Float:min_y, Float:min_z,
		Float:max_x, Float:max_y, Float:max_z
	;
	ModelGeom_parseBoxBounds(ModelVisual_AABB3[modelid], min_x, min_y, min_z, max_x, max_y, max_z);
	size_x = max_x - min_x;
	size_y = max_y - min_y;
	size_z = max_z - min_z;
}

//	Get center position of AABB3 of visible object.
stock ModelGeom_getVisualCenter(
	const modelid,
	&Float:pos_x,
	&Float:pos_y,
	&Float:pos_z
) {
	new Float:min_x, Float:min_y, Float:min_z,
		Float:max_x, Float:max_y, Float:max_z
	;
	ModelGeom_parseBoxBounds(ModelVisual_AABB3[modelid], min_x, min_y, min_z, max_x, max_y, max_z);
	pos_x = 0.5 * (max_x - min_x);
	pos_y = 0.5 * (max_y - min_y);
	pos_z = 0.5 * (max_z - min_z);
}
#endif
