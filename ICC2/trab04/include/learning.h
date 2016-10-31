#ifndef _LERANING_H_
#define _LERANING_H_

double *train(char *img, int ***masks, int maskDim, int nMasks, int *dim);
int *k_nearest_neightboors(int kNearest, double *test, double **trainVec, int nimgs, int line);
#endif
