#include "PaintModel.h"
#include <algorithm>
#include <wx/dcmemory.h>
#include <iostream>

PaintModel::PaintModel()
:mPen(*wxBLACK_PEN)
,mBrush(*wxWHITE_BRUSH)
{

}

// Draws any shapes in the model to the provided DC (draw context)
void PaintModel::DrawShapes(wxDC& dc, bool showSelection)
{
	// TODO
    if (mBitmap.IsOk())
    {
        dc.DrawBitmap(mBitmap, 0, 0);
    }
    for (auto iter = mShapes.begin(); iter != mShapes.end(); iter++)
    {
        iter->get()->Draw(dc);
    }
    if (mSelectedShape != nullptr)
    {
        mSelectedShape->DrawSelection(dc);
    }
    
}

// Clear the current paint model and start fresh
void PaintModel::New()
{
	// TODO
    mShapes.clear();
    while (!mUndoStack.empty())
    {
        mUndoStack.pop();
    }
    while (!mRedoStack.empty())
    {
        mRedoStack.pop();
    }
    mPen = *wxBLACK_PEN;
    mBrush = *wxWHITE_BRUSH;
    mActiveCommand = nullptr;
    if (mBitmap.IsOk())
    {
        mBitmap = wxBitmap();
    }
    
}

// Add a shape to the paint model
void PaintModel::AddShape(std::shared_ptr<Shape> shape)
{
	mShapes.emplace_back(shape);
}

// Remove a shape from the paint model
void PaintModel::RemoveShape(std::shared_ptr<Shape> shape)
{
	auto iter = std::find(mShapes.begin(), mShapes.end(), shape);
	if (iter != mShapes.end())
	{
		mShapes.erase(iter);
	}
}

// Returns true if there's currently and active command
bool PaintModel::HasActiveCommand()
{
    if (mActiveCommand.get() != nullptr)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool PaintModel::HasSelectedShape()
{
    if (mSelectedShape.get() != nullptr)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void PaintModel::CreateCommand(CommandType type, wxPoint& start)
{
    mActiveCommand = CommandFactory::Create(this->shared_from_this(), type, start);
    while (!mRedoStack.empty())
    {
        mRedoStack.pop();
    }
}

void PaintModel::UpdateCommand(wxPoint& point)
{
    mActiveCommand.get()->Update(point);
}

void PaintModel::FinalizeCommand()
{
    mActiveCommand.get()->Finalize(this->shared_from_this());
    mUndoStack.push(mActiveCommand);
    mActiveCommand.reset();
}

bool PaintModel::CanUndo()
{
    if (static_cast<int>(mUndoStack.size()) > 0)
    {
        return true;
        
    }
    else
    {
        return false;
    }
}

bool PaintModel::CanRedo()
{
    if (static_cast<int>(mRedoStack.size()) > 0)
    {
        return true;
        
    }
    else
    {
        return false;
    }
}

void PaintModel::Undo()
{
    
    std::shared_ptr<Command> command = mUndoStack.top();
    mUndoStack.pop();
    command->Undo(this->shared_from_this());
    mRedoStack.push(command);
    
}

void PaintModel::Redo()
{
    std::shared_ptr<Command> command = mRedoStack.top();
    mRedoStack.pop();
    command->Redo(this->shared_from_this());
    mUndoStack.push(command);
}

int PaintModel::GetPenWidth()
{
    return mPen.GetWidth();
}

wxColour PaintModel::GetPenColor()
{
    return mPen.GetColour();
}

void PaintModel::SetPenWidth(int width)
{
    mPen.SetWidth(width);
}

void PaintModel::SetPenColor(wxColour color)
{
//    if (mSelectedShape != nullptr)
//    {
//        mPen.SetColour(color);
//        wxPoint topLeft;
//        wxPoint botRight;
//        mSelectedShape->GetBounds(topLeft, botRight);
//        this->CreateCommand(CM_SetPen, topLeft);
//    }
//    else
    //{
        mPen.SetColour(color);
    //}
    
}

wxColour PaintModel::GetBrushColor()
{
    return mBrush.GetColour();
}

void PaintModel::SetBrushColor(wxColour color)
{
    mBrush.SetColour(color);
}

wxPen PaintModel::GetPen()
{
    return mPen;
}

void PaintModel::SetPen(wxPen pen)
{
    mPen = pen;
}

wxBrush PaintModel::GetBrush()
{
    return mBrush;
}

void PaintModel::setBrush(wxBrush brush)
{
    mBrush = brush;
}

std::shared_ptr<Shape> PaintModel::GetSelectedShape()
{
    return mSelectedShape;
}

void PaintModel::RemoveSelectedShape()
{
    mSelectedShape = nullptr;
}

void PaintModel::IntersectPoint(wxPoint& point)
{
    for (auto riter = mShapes.rbegin(); riter != mShapes.rend(); ++riter)
    {
        if (riter->get()->Intersects(point))
        {
            mSelectedShape = *riter;
            break;
        }
        else
        {
            mSelectedShape = nullptr;
        }
    }
}

void PaintModel::ExportFile(wxString fileName, wxSize size)
{
    wxBitmap bitmap;
    bitmap.Create(size);
    wxMemoryDC dc(bitmap);
    dc.SetBackground(*wxWHITE_BRUSH);
    dc.Clear();
    mSelectedShape = nullptr;
    DrawShapes(dc);
 
    size_t lastindex = fileName.find_last_of(".");
    wxString extension = fileName.substr(0, lastindex);
    if (strcmp(extension, "png"))
    {
        bitmap.SaveFile(fileName, wxBITMAP_TYPE_PNG);
    }
    else if (strcmp(extension, "bmp"))
    {
        bitmap.SaveFile(fileName, wxBITMAP_TYPE_BMP);
    }
    else if (strcmp(extension, "jpeg") || strcmp(extension, "jpg"))
    {
        bitmap.SaveFile(fileName, wxBITMAP_TYPE_JPEG);
    }
}

void PaintModel::LoadImport(wxString fileName)
{
    this->New();
    size_t lastindex = fileName.find_last_of(".");
    wxString extension = fileName.substr(0, lastindex);
    if (strcmp(extension, "png"))
    {
        std::cout << "It is .png" << std::endl;
        if (!mBitmap.IsOk())
        {
            std::cout << "In here" << std::endl;
            mBitmap.LoadFile(fileName, wxBITMAP_TYPE_PNG);
//            wxMemoryDC dc(mBitmap);
//            dc.SetBackground(*wxWHITE_BRUSH);
//            dc.Clear();
//            DrawShapes(dc);
        }
    }
    else if (strcmp(extension, "bmp"))
    {
        std::cout << "It is .bmp" << std::endl;
        if (!mBitmap.IsOk())
        {
            mBitmap.LoadFile(fileName, wxBITMAP_TYPE_BMP);
        }
    }
    else if (strcmp(extension, "jpeg") || strcmp(extension, "jpg"))
    {
        std::cout << "It is .jpeg or .jpg" << std::endl;
        if (!mBitmap.IsOk())
        {
            mBitmap.LoadFile(fileName, wxBITMAP_TYPE_JPEG);
        }
    }
    
}

