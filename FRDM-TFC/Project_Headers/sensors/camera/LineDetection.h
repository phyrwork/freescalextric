/* LineDetection.h
 * ===========================================
 * This library contains the methods required
 * to determine the position of the car 
 * relative to the sides of the track.
 * -------------------------------------------
 * Adapted from the 2014 tracking algorithm by
 * MW. Uses the same principle of probabilites
 * to choose most likely target to follow, but
 * is modified to follow the 2015 competition
 * track with lines at both sides of the
 * course.
 * -------------------------------------------
 * Author: Connor Newton
 * Date:   November 17, 2014
 */

#ifndef LINEDETECTION_H_
#define LINEDETECTION_H_

#include "support/Probability.h"
#include "support/carState_s.h"

//findLines
#define DIFFERENTIAL_THRESHOLD    300
#define HEIGHT_THRESHOLD          600
#define MAX_LOST_LINE_DURATION    10000
#define LOST_LINE_RESET_DURATION  10000
#define MAX_NUMBER_OF_TRANSITIONS 16
#define MIN_CERTAINTY             0.2f

//weightEdges
#define EDGE_DPOS_SD   10
#define EDGE_DPOS_MEAN 0

//weightLines
#define LINE_WIDTH_SD    10
#define LINE_WIDTH_MEAN  95
#define LINE_DWIDTH_SD   15
#define LINE_DWIDTH_MEAN 0

//findStopLine
#define STOP_MIN_CERTAINTY   0.6f
#define STOP_LINE_WIDTH_SD   5
#define STOP_LINE_WIDTH_MEAN 15
#define STOP_LINE_GAP_SD 5
#define STOP_LINE_GAP_MEAN 10

typedef uint8_t EdgeType;
#define EDGE_TYPE_RISING  0
#define EDGE_TYPE_FALLING 1
#define EDGE_TYPE_VIRTUAL 255

#define LINE_TYPE_WHITE EDGE_TYPE_RISING
#define LINE_TYPE_BLACK EDGE_TYPE_FALLING

typedef struct {
	EdgeType type; //Type of edge (i.e. rising/falling)
	uint8_t  pos;  //Location of edge
	float    P_dPos[2];
	float    P_edge[2];
} Edge_s;

typedef struct {
	Edge_s    edges[2];
  //#define start  edges[0].pos
  //#define finish edges[1].pos
	uint8_t width;
	float   P_width;
	float   P_dWidth;
	float   P_newLine;
	float   P_absLine;
	float   P_relLine;
} Line_s;

typedef uint8_t PositioningState;
#define POSITIONING_STATE_FULL 0
#define POSITIONING_STATE_PARTIAL_LEFT 10
#define POSITIONING_STATE_PARTIAL_RIGHT 20
#define POSITIONING_STATE_PARTIAL_NONE 255

typedef struct {
	Line_s    lines[3];
  //#define lineA lines[0]
  //#define lineB lines[2]
  //#define gap   lines[1]
	float   P_lineA;
	float   P_lineB;
	float   P_gap;
	float   P_stop;
} StopLine;

void    findPosition(int16_t *dy, carState_s* carState);
uint8_t findEdges(Edge_s *edges, int16_t* dy, uint16_t dy_t, uint16_t ry_t);
uint8_t findLines(Line_s *lines, Edge_s *edges, uint8_t numEdges, uint8_t const type);
void    weightEdges(Edge_s *targetEdges, Edge_s *edges, uint8_t numEdges);
int8_t  weightLines(Line_s* trackedLine, Line_s* lines, uint8_t numLines);
uint8_t findStop(Line_s* lines, uint8_t numLines);
void    preloadProbabilityTables();
void    diff(volatile uint16_t* input, int16_t* output, uint8_t length);

/* Data sharing for telemetry */
extern PositioningState positioningState; // Line_s tracking status
extern Line_s             TargetLine;	// Current model line
extern int8_t           trackPosition;     // Current detected road position

#endif /* LINEDETECTION_H_ */
