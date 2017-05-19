#pragma once
#include <memory>
#include <vector>
#include <stack>
#include "Shape.h"
#include "Command.h"
#include <wx/bitmap.h>
#include <wx/pen.h>
#include <wx/brush.h>

class PaintModel : public std::enable_shared_from_this<PaintModel>
{
public:
	PaintModel();
	
	// Draws any shapes in the model to the provided DC (draw context)
	void DrawShapes(wxDC& dc, bool showSelection = true);

	// Clear the current paint model and start fresh
	void New();

	// Add a shape to the paint model
	void AddShape(std::shared_ptr<Shape> shape);
	// Remove a shape from the paint model
	void RemoveShape(std::shared_ptr<Shape> shape);
    // Returns true if there's currently and active command
    bool HasActiveCommand();
    bool HasSelectedShape();
    void CreateCommand(CommandType type, wxPoint& start);
    void UpdateCommand(wxPoint& point);
    void FinalizeCommand();
    
    bool CanUndo();
    bool CanRedo();
    void Undo();
    void Redo();
    
    int GetPenWidth();
    wxColour GetPenColor();
    void SetPenWidth(int width);
    void SetPenColor(wxColour color);
    wxColour GetBrushColor();
    void SetBrushColor(wxColour color);
    wxPen GetPen();
    void SetPen(wxPen pen);
    wxBrush GetBrush();
    void setBrush(wxBrush brush);
    
    std::shared_ptr<Shape> GetSelectedShape();
    void RemoveSelectedShape();
    
    void IntersectPoint(wxPoint& point);
    
    void ExportFile(wxString fileName, wxSize size);
    void LoadImport(wxString fileName);
    
private:
	// Vector of all the shapes in the model
	std::vector<std::shared_ptr<Shape>> mShapes;
    // Shared pointer to the active Command
    std::shared_ptr<Command> mActiveCommand;
    // Undo stack
    std::stack<std::shared_ptr<Command>> mUndoStack;
    // Redo stack
    std::stack<std::shared_ptr<Command>> mRedoStack;
    // Pen
    wxPen mPen;
    // Brush
    wxBrush mBrush;
    // Selected shape
    std::shared_ptr<Shape> mSelectedShape;
    // Store bitmap
    wxBitmap mBitmap;
};
