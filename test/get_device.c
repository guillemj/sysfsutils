/*
 * get_device.c
 *
 * Utility to get details of a given device
 *
 * Copyright (C) IBM Corp. 2003
 *
 *      This program is free software; you can redistribute it and/or modify it
 *      under the terms of the GNU General Public License as published by the
 *      Free Software Foundation version 2 of the License.
 *
 *      This program is distributed in the hope that it will be useful, but
 *      WITHOUT ANY WARRANTY; without even the implied warranty of
 *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *      General Public License for more details.
 *
 *      You should have received a copy of the GNU General Public License along
 *      with this program; if not, write to the Free Software Foundation, Inc.,
 *      675 Mass Ave, Cambridge, MA 02139, USA.
 *
 */

#include <stdio.h>
#include <stdlib.h>

#include "libsysfs.h"

void print_usage(void)
{
        fprintf(stdout, "Usage: get_device [device]\n");
}

int main(int argc, char *argv[])
{
	char *bus = NULL;
	struct sysfs_device *device = NULL;
	struct sysfs_attribute *attr = NULL;

	if (argc != 2) {
		print_usage();
		return 1;
	}

	bus = (char *)calloc(1, SYSFS_NAME_LEN);
	if ((sysfs_find_device_bus(argv[1], bus, SYSFS_NAME_LEN)) < 0) {
		fprintf(stdout, "Device %s not found\n", argv[1]);
		free (bus);
		return 1;
	}
	fprintf(stdout, "Device %s is a member of bus %s\n", 
			argv[1], bus);
	device = sysfs_open_device_by_id(argv[1], bus, SYSFS_NAME_LEN);
	if (device == NULL) {
		fprintf(stdout, "Device %s not found\n", argv[1]);
		free(bus);
		return 1;
	}
	dlist_for_each_data(device->directory->attributes, attr, 
					struct sysfs_attribute) {
		fprintf(stdout, "\t%s : %s", attr->name, attr->value);
	}
	fprintf(stdout, "\n");
	
	sysfs_close_device(device);
	free(bus);
	return 0;
}

