#include "Command.h"
#include "Shape.h"
#include "PaintModel.h"
#include <iostream>

Command::Command(const wxPoint& start, std::shared_ptr<Shape> shape)
	:mStartPoint(start)
	,mEndPoint(start)
	,mShape(shape)
{

}

// Called when the command is still updating (such as in the process of drawing)
void Command::Update(const wxPoint& newPoint)
{
	mEndPoint = newPoint;
}

std::shared_ptr<Command> CommandFactory::Create(std::shared_ptr<PaintModel> model,
	CommandType type, const wxPoint& start)
{
	std::shared_ptr<Command> retVal;
	
	// TODO: Actually create a command based on the type passed in
    if (type == CM_DrawRect)
    {
        std::shared_ptr<Shape> rect = std::make_shared<RectShape>(start);
        rect->SetPen(model->GetPen());
        rect->SetBrush(model->GetBrush());
        retVal = std::make_shared<DrawCommand>(start, rect);
        model->AddShape(rect);
    }
    else if (type == CM_DrawEllipse)
    {
        std::shared_ptr<Shape> ellip = std::make_shared<EllipShape>(start);
        ellip->SetPen(model->GetPen());
        ellip->SetBrush(model->GetBrush());
        retVal = std::make_shared<DrawCommand>(start, ellip);
        model->AddShape(ellip);
    }
    else if (type == CM_DrawLine)
    {
        std::shared_ptr<Shape> line = std::make_shared<LineShape>(start);
        line->SetPen(model->GetPen());
        line->SetBrush(model->GetBrush());
        retVal = std::make_shared<DrawCommand>(start, line);
        model->AddShape(line);
    }
    else if (type == CM_DrawPencil)
    {
        std::shared_ptr<Shape> pencil = std::make_shared<PencilShape>(start);
        pencil->SetPen(model->GetPen());
        pencil->SetBrush(model->GetBrush());
        retVal = std::make_shared<DrawCommand>(start, pencil);
        model->AddShape(pencil);
    }
    else if (type == CM_SetPen)
    {
        retVal = std::make_shared<SetPenCommand>(start, model->GetSelectedShape());
    }
    else if (type == CM_SetBrush)
    {
        retVal = std::make_shared<SetBrushCommand>(start, model->GetSelectedShape());
    }
    else if (type == CM_Delete)
    {
        retVal = std::make_shared<DeleteCommand>(start, model->GetSelectedShape());
        model->RemoveShape(model.get()->GetSelectedShape());
    }
    
	return retVal;
}

DrawCommand::DrawCommand(const wxPoint& start, std::shared_ptr<Shape> shape) : Command(start, shape)
{
    
}

void DrawCommand::Update(const wxPoint &newPoint)
{
    Command::Update(newPoint);
    mShape->Update(newPoint);
    
}

void DrawCommand::Finalize(std::shared_ptr<PaintModel> model)
{
    mShape->Finalize();
}

void DrawCommand::Undo(std::shared_ptr<PaintModel> model)
{
    model->RemoveShape(mShape);
}

void DrawCommand::Redo(std::shared_ptr<PaintModel> model)
{
    model->AddShape(mShape);
}

SetPenCommand::SetPenCommand(const wxPoint& start, std::shared_ptr<Shape> shape) : Command(start, shape)
{
    mOldPen = shape.get()->GetPen();
}

void SetPenCommand::Finalize(std::shared_ptr<PaintModel> model)
{
    mNewPen = model->GetPen();
    mShape->SetPen(mNewPen);
}

void SetPenCommand::Undo(std::shared_ptr<PaintModel> model)
{
    mShape->SetPen(mOldPen);
}

void SetPenCommand::Redo(std::shared_ptr<PaintModel> model)
{
    mShape->SetPen(mNewPen);
}

SetBrushCommand::SetBrushCommand(const wxPoint& start, std::shared_ptr<Shape> shape) : Command(start, shape)
{
    mOldBrush = shape.get()->GetBrush();
}

void SetBrushCommand::Finalize(std::shared_ptr<PaintModel> model)
{
    mNewBrush = model->GetBrush();
    mShape->SetBrush(mNewBrush);
}

void SetBrushCommand::Undo(std::shared_ptr<PaintModel> model)
{
    mShape->SetBrush(mOldBrush);
}

void SetBrushCommand::Redo(std::shared_ptr<PaintModel> model)
{
    mShape->SetBrush(mNewBrush);
}

DeleteCommand::DeleteCommand(const wxPoint& start, std::shared_ptr<Shape> shape) : Command(start, shape)
{
    mDeletedShape = shape;
}

void DeleteCommand::Finalize(std::shared_ptr<PaintModel> model)
{
    model.get()->GetSelectedShape()->Finalize();
}

void DeleteCommand::Undo(std::shared_ptr<PaintModel> model)
{
    model->AddShape(mDeletedShape);
}

void DeleteCommand::Redo(std::shared_ptr<PaintModel> model)
{
    model->RemoveShape(mDeletedShape);
}


