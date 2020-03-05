#pragma once

namespace IDFlags
{

	enum
	{
		// I use this ISceneNode ID to indicate a scene node that is
		// not pickable by getSceneNodeAndCollisionPointFromRay()
		IsNotPickable = 0,

		// I use this flag in ISceneNode IDs to indicate that the
		// scene node can be picked by ray selection.
		IsPickable = 1 << 0,

		// I use this flag in ISceneNode IDs to indicate that the
		// scene node can be highlighted.  In this example, the
		// homonids can be highlighted, but the level mesh can't.
		IsHighlightable = 1 << 1
	};
}