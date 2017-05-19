#include "Shape.h"
#include <iostream>

Shape::Shape(const wxPoint& start)
	:mStartPoint(start)
	,mEndPoint(start)
	,mTopLeft(start)
	,mBotRight(start)
{

}

// Tests whether the provided point intersects
// with this shape
bool Shape::Intersects(const wxPoint& point) const
{
	wxPoint topleft;
	wxPoint botright;
	GetBounds(topleft, botright);
	if (point.x >= topleft.x && point.x <= botright.x &&
		point.y >= topleft.y && point.y <= botright.y)
	{
		return true;
	}
	else
	{
		return false;
	}
}

// Update shape with new provided point
void Shape::Update(const wxPoint& newPoint)
{
	mEndPoint = newPoint;

	// For most shapes, we only have two points - start and end
	// So we can figure out the top left/bottom right bounds
	// based on this.
	mTopLeft.x = std::min(mStartPoint.x, mEndPoint.x);
	mTopLeft.y = std::min(mStartPoint.y, mEndPoint.y);
	mBotRight.x = std::max(mStartPoint.x, mEndPoint.x);
	mBotRight.y = std::max(mStartPoint.y, mEndPoint.y);
}

void Shape::Finalize()
{
	// Default finalize doesn't do anything
}

void Shape::GetBounds(wxPoint& topLeft, wxPoint& botRight) const
{
	topLeft = mTopLeft;
	botRight = mBotRight;
}

int Shape::GetPenWidth()
{
    return mPen.GetWidth();
}

wxColour Shape::GetPenColor()
{
    return mPen.GetColour();
}

void Shape::SetPenWidth(int width)
{
    mPen.SetWidth(width);
}

void Shape::SetPenColor(wxColour color)
{
    mPen.SetColour(color);
}

wxColour Shape::GetBrushColor()
{
    return mBrush.GetColour();
}

void Shape::SetBrushColor(wxColour color)
{
    mBrush.SetColour(color);
}

wxPen Shape::GetPen()
{
    return mPen;
}

void Shape::SetPen(wxPen pen)
{
    mPen = pen;
}

wxBrush Shape::GetBrush()
{
    return mBrush;
}

void Shape::SetBrush(wxBrush brush)
{
    mBrush = brush;
}

void Shape::DrawSelection(wxDC &dc)
{
    dc.SetPen(*wxBLACK_DASHED_PEN);
    dc.SetBrush(*wxTRANSPARENT_BRUSH);
    dc.DrawRectangle(wxRect(wxPoint(mTopLeft.x-5, mTopLeft.y-5), wxPoint(mBotRight.x+5, mBotRight.y+5)));
    
}

wxPoint Shape::getStartPoint()
{
    return mStartPoint;
}

RectShape::RectShape(const wxPoint& start) : Shape(start)
{
    
}

void RectShape::Draw(wxDC &dc) const
{
    dc.SetPen(mPen);
    dc.SetBrush(mBrush);
    dc.DrawRectangle(wxRect(mTopLeft, mBotRight));
}

EllipShape::EllipShape(const wxPoint& start) : Shape(start)
{
    
}

void EllipShape::Draw(wxDC &dc) const
{
    dc.SetPen(mPen);
    dc.SetBrush(mBrush);
    dc.DrawEllipse(wxRect(mTopLeft, mBotRight));
}

LineShape::LineShape(const wxPoint& start) : Shape(start)
{
    
}

void LineShape::Draw(wxDC &dc) const
{
    dc.SetPen(mPen);
    dc.SetBrush(mBrush);
    dc.DrawLine(mStartPoint, mEndPoint);
}

PencilShape::PencilShape(const wxPoint& start) : Shape(start)
{
    mPoints.push_back(start);
}

void PencilShape::Draw(wxDC &dc) const
{
    dc.SetPen(mPen);
    dc.SetBrush(mBrush);
    if (static_cast<int>(mPoints.size()) == 1)
    {
        dc.DrawLine(mStartPoint, mEndPoint);
    }
    else if (static_cast<int>(mPoints.size()) > 1)
    {
        dc.DrawLines(static_cast<int>(mPoints.size()), &mPoints[0]);
    }
}

void PencilShape::Update(const wxPoint& newPoint)
{
    Shape::Update(newPoint);
    mPoints.push_back(newPoint);
}

void PencilShape::Finalize()
{
    int topLeftX = mPoints.begin()->x;
    int topLeftY = mPoints.begin()->y;
    int botRightX = mPoints.begin()->x;
    int botRightY = mPoints.begin()->y;
    for (auto iter = mPoints.begin(); iter != mPoints.end(); iter++)
    {
        if (iter->x < topLeftX)
        {
            topLeftX = iter->x;
        }
        if (iter->x > botRightX)
        {
            botRightX = iter->x;
        }
        if (iter->y > botRightY)
        {
            botRightY = iter->y;
        }
        if (iter->y < topLeftY)
        {
            topLeftY = iter->y;
        }
    }
    mTopLeft = wxPoint(topLeftX, topLeftY);
    mBotRight = wxPoint(botRightX, botRightY);
}



