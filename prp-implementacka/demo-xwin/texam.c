/*implementation of texam.c for prp*/

// libraries
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <errno.h>

// test modules
#include "exam_utils.h"
#include "save_jpeg.h"
#include "xwin_sdl.h"

// constants
#ifndef EXIT_SUCCESS
#define EXIT_SUCCESS 0
#endif

#define ERR_START 100
#define ERR_FILE 101
#define ERR_CMD 102
#define ERR_IMG 103
#define SWAP 's'
#define COPY 'c'

// local function declarations
bool process_file(FILE *f_cmds, unsigned char *img, int image_w, int image_h, bool anim);
bool transform(unsigned char *img, int image_w, int image_h, int x1, int y1, int w, int h, int x2, int y2, int command);
void err_exit(int exit_code);
bool in_img(int pos, int max_val);

// MAIN -----------------------------------------------------------
int main(int argc, char const *argv[])
{
	// I read arguments
	const char *f_image = argc > 1 ? argv[1] : NULL;
	const char *f_cmds = argc > 2 ? argv[2] : NULL;
	const char *f_out = argc > 3 ? argv[3] : NULL;
	const bool anim = (argc > 4) && (strcmp(argv[4], "--anim") == 0);

	if ((f_image == NULL) || (f_cmds == NULL) || (f_out == NULL))
		err_exit(ERR_START);

	// II read image
	int image_w = 0;
	int image_h = 0;
	unsigned char *img = xwin_load_image(f_image, &image_w, &image_h);
	if (img == NULL)
		err_exit(ERR_IMG);

	if (anim)
		xwin_init(image_w, image_h);

	// III process commands
	FILE *o_file = fopen(f_cmds, "r");
	if (o_file == NULL)
	{
		free(img);
		if (anim)
			xwin_close();
		err_exit(ERR_FILE);
	}

	if (!process_file(o_file, img, image_w, image_h, anim))
	{
		free(img);
		if (anim)
			xwin_close();
		err_exit(ERR_CMD);
	}

	// IV save output
	if (strstr(f_out, ".jpg") || strstr(f_out, ".jpeg"))
	{
		save_image_jpeg(image_w, image_h, img, f_out);
	}
	else
	{
		save_image_rgb(image_w, image_h, img, f_out);
	}

	// V clean up and exit
	free(img);
	if (anim)
		xwin_close();
	exit(EXIT_SUCCESS);
}
// EO_MAIN -----------------------------------------------------------

// local function implementation

// function -----------------------------------------------------------
/*exits program with exit_code, and writes phrase to stderr
that is asociated with that exit_code*/
void err_exit(int exit_code)
{
	char *err_msg = NULL;
	switch (exit_code)
	{
	case ERR_START:
		err_msg = "program should be started as: ./texam input_image commands_file output_file (--anim).";
		break;
	case ERR_FILE:
		err_msg = "Can't open file.";
		break;
	case ERR_CMD:
		err_msg = "Something went wrong with commands.";
		break;
	case ERR_IMG:
		err_msg = "Can't load image";
		break;
	}
	fprintf(stderr, "ERROR: %s\n", err_msg);
	exit(exit_code);
}

// function -----------------------------------------------------------
/*processes commands from f_cmds in an img of size image_w * image_h,
animates if anim = true

returns true on success, false otherwise*/
bool process_file(FILE *f_cmds, unsigned char *img, int image_w, int image_h, bool anim)
{
	bool ret = true;
	int x1, x2, y1, y2, w, h;
	char cmd[3];
	int counter = 0;

	while ((!feof(f_cmds)) && ret)
	{
		int cmd_line = fscanf(f_cmds, "%2s %d %d %d %d %d %d", cmd, &x1, &y1, &w, &h, &x2, &y2);

		if ((cmd_line == 7) && (strcmp(cmd, "sw") == 0))
		{
			ret = transform(img, image_w, image_h, x1, y1, w, h, x2, y2, SWAP);
		}
		else if ((cmd_line == 7) && (strcmp(cmd, "cp") == 0))
		{
			ret = transform(img, image_w, image_h, x1, y1, w, h, x2, y2, COPY);
		}
		else // error
		{
			ret = false;
			break;
		}

		counter += 1;
		if (anim && (counter % 15 == 0))
		{
			xwin_redraw(image_w, image_h, img);
		}
	}

	return ret;
}

// function -----------------------------------------------------------
/*checks if position is valid (in range <0 ; max_val))

return true if so, false otherwise*/
bool in_img(int pos, int max_val)
{
	bool ret = false;
	if ((pos >= 0) || pos < (max_val))
		ret = true;
	return ret;
}

// function -----------------------------------------------------------
/*copies or swaps zone in img of size w * h starting on [x1,y1],
to zone of same size starting on [x2,y2]

returns true on success, false othewise*/
bool transform(unsigned char *img, int image_w, int image_h, int x1, int y1, int w, int h, int x2, int y2, int command)
{
	for (int xi = 0; xi < w; ++xi)
	{
		for (int yi = 0; yi < h; ++yi)
		{
			int sx = x1 + xi;
			int sy = y1 + yi;
			int dx = x2 + xi;
			int dy = y2 + yi;

			if (!(in_img(sx, image_w) && in_img(sy, image_h) &&
				  in_img(dx, image_w) && in_img(dy, image_h)))
			{
				fprintf(stderr, "Error: wrong size in commands file.");
				return false;
			}

			for (int rgb = 0; rgb < 3; ++rgb)
			{
				int d_pxl = (dy * image_w + dx) * 3 + rgb;
				int s_pxl = (sy * image_w + sx) * 3 + rgb;

				switch (command)
				{
				case SWAP:
				{
					unsigned char tmp = img[s_pxl];
					img[s_pxl] = img[d_pxl];
					img[d_pxl] = tmp;
					break;
				}
				case COPY:
				{
					img[d_pxl] = img[s_pxl];
					break;
				}
				}
			}
		}
	}
	return true;
}

/*end of texam.c*/
