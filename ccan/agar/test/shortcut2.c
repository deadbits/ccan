#include "config.h"

#include <assert.h>

#include <ccan/container_of/container_of.h>
#include <ccan/ptrint/ptrint.h>

#include <ccan/agar/agar.h>

#include "simple-graphr.h"

static const void *shortcut2_first_edge_r(const struct agar_graph *gr,
					  const void *nr)
{
	int ni = ptr2int(nr);

	switch (ni) {
	case 1:
	case 2:
		return int2ptr(1);

	case 3:
		return NULL;

	default:
		assert(0);
	}
}

static const void *shortcut2_next_edge_r(const struct agar_graph *gr,
					 const void *nr, const void *e)
{
	int ni = ptr2int(nr);
	int index = ptr2int(e);

	switch (ni) {
	case 1:
		if (index == 1)
			return int2ptr(2);
		assert(index == 2);
		return NULL;

	case 2:
		assert(index == 1);
		return NULL;

	default:
		assert(0);
	}
}

static int shortcut2_edge_info_r(const struct agar_graph *gr,
				 const void *nr, const void *e,
				 struct agar_edge_info *eir)
{
	int ni = ptr2int(nr);
	int index = ptr2int(e);

	switch (ni) {
	case 1:
		if (index == 1) {
			eir->to = int2ptr(3);
		} else {
			assert(index == 2);
			eir->to = int2ptr(2);
		}
		eir->icost = 2;
		break;

	case 2:
		assert(index == 1);
		eir->to = int2ptr(3);
		eir->icost = -1;
		break;

	default:
		assert(0);
	}
	return 0;
}

void shortcut2_graphr_init(struct shortcut2_graphr *s1gr)
{
	agar_init_graph(&s1gr->gr, shortcut2_first_edge_r,
			shortcut2_next_edge_r,
			shortcut2_edge_info_r);
}
