#include "ImgPanel.h"

BEGIN_EVENT_TABLE(PDFPanel, wxPanel)
EVT_PAINT(PDFPanel::paintEvent)
EVT_LEFT_UP(PDFPanel::OnClick)
EVT_KEY_DOWN(PDFPanel::OnKeyPressed)
END_EVENT_TABLE()
class temp;
PDFPanel::PDFPanel(wxWindow * parent):wxScrolledWindow(parent)
{
    //bitmap = new wxBitmap("C:\\crate.bmp");
    doc32 = new Document("C:\\wX.pdf");
    bitmap = doc32->renderPDF();
    w = bitmap->GetWidth();
    h = bitmap->GetHeight();
    scale = (float)doc32->getPDFHeight()/h;
    SetScrollbars(1,1,w,h,0,0);
    SetScrollRate(10,10);
    SetDropTarget(new temp(this));
    selectedItems.reserve(51);
  //  wxMessageBox(wxString::Format("%i-%i",s.GetHeight(),s.GetWidth()));
    pen = wxPen(*wxBLUE,2,wxSOLID );
    grid = Grid(40,w,h,15);
}

void PDFPanel::paintEvent(wxPaintEvent & evt)
{
    wxPaintDC dc(this);
    DoPrepareDC(dc);
    render(dc);
}

void PDFPanel::render(wxDC& dc)
{
    it = selectedItems.begin();
    if(bitmap->IsOk() && bitmap!=NULL)
    {
        dc.DrawBitmap( *bitmap,0 ,0, false );
        grid.DrawGrid(dc);
        while(it!=selectedItems.end())
        {
            wxRect rect = (it->rect);
            dc.SetPen(pen);
            dc.SetBrush(*wxTRANSPARENT_BRUSH);
            dc.DrawRectangle(rect);
            it++;
        }
    }

}

/*void PDFPanel::renderPDF(char *filename, int pagenumber, int zoom, int rotation)
{
    if(pagenumber==0)
        pagenumber = curPage;
    else
        curPage = pagenumber;
    // Create a context to hold the exception stack and various caches.
    if(bitmap!=NULL)
        delete bitmap;
	fz_context *ctx = fz_new_context(NULL, NULL, FZ_STORE_UNLIMITED);

	// Register the default file types.

	fz_register_document_handlers(ctx);

	// Open the PDF, XPS or CBZ document.

	fz_document *doc = fz_open_document(ctx, filename);

	// Retrieve the number of pages (not used in this example).

	pagecount = fz_count_pages(doc);
    fz_page *page = fz_load_page(doc, pagenumber - 1);
	// Load the page we want. Page numbering starts from zero.
	pdf_document * pdoc =  pdf_specifics(doc);
    pdf_obj * form,*b;
    b = pdf_new_bool(pdoc,1);
    form = pdf_dict_getp(pdf_trailer(pdoc), "Root/AcroForm/Fields");

	pdf_annot * wid = (pdf_annot*)(pdf_first_widget(pdoc,(pdf_page*)page));
	int res = pdf_text_widget_set_text(pdoc,(pdf_widget*)wid,"FFFF");
	//char * mes = pdf_field_value(pdoc,wid->obj);

	fz_point p = {10,20};
    pdf_annot * wid1 = (pdf_annot*)pdf_create_widget(pdoc,(pdf_page*)page,PDF_WIDGET_TYPE_TEXT,"Tarun");
    fz_rect rect = {10,20,100,100};
    wid1->rect = rect;
    pdf_text_widget_set_text(pdoc,(pdf_widget*)wid1,"FFFdddddddF");
    //pdf_dict_puts(wid1->obj,"V",pdf_new_string(pdoc,"DDDDDD",6));
    char*mes = pdf_field_name(pdoc,wid->obj);
    pdoc->update_appearance(pdoc,wid);
    pdoc->update_appearance(pdoc,wid1);
    wote = pdf_dict_get_val(form,1);
    wxPdfDocument pdf;
    pdf_annot*att = (pdf_annot*)pdf_next_widget((pdf_widget*)wid);
    int i1 = pdf_text_widget_max_len(pdoc,(pdf_widget*)att);
    //char * mes2 = pdf_text_widget_text(pdoc,(pdf_widget*)att);
	wxMessageBox(mes);
	//pfd_widget * wid1 = pdf_create_widget(pdoc,(pdf_page*)page,PDF_WIDGET_TYPE_TEXT,"tarun");

	//pdf_bound_widget()
    /*pdf_document * pdoc =  pdf_specifics(doc);
	//pdf_page * pg = pdf_load_page(pdoc,0);
    pdf_obj * form,*field;
    form = pdf_dict_getp(pdf_trailer(pdoc), "Root/AcroForm/Fields");
    field = pdf_lookup_field(form,"name");
    pdf_field_set_value(pdoc,field,"DDDD");
    char * mes = pdf_field_value(pdoc,field);
    pdf_update_page(pdoc, (pdf_page *)page);
    wxMessageBox(mes);
  //  pdf_close_document(pdoc);
	// Calculate a transform to use when rendering. This transform
	// contains the scale and rotation. Convert zoom percentage to a
	// scaling factor. Without scaling the resolution is 72 dpi.

	fz_matrix transform,tran;
	fz_rotate(&transform, rotation);
	fz_pre_scale(&transform, zoom / 100.0f, zoom / 100.0f);
    fz_translate(&tran,100,350);

   // pdf_field_set_display(pdoc,wid->obj,3);
	// Take the page bounds and transform them by the same matrix that
	// we will use to render the page.

	fz_rect bounds;
	fz_bound_page(doc, page, &bounds);
//	pdf_bound_widget((pdf_widget*)wid1,&bounds);
	fz_transform_rect(&bounds, &transform);
    pdf_text_widget_set_text(pdoc,(pdf_widget*)wid1,"FFFFFFFFFFFFFFFFFFFFFFFFFF");
    pdf_update_appearance(pdoc,wid1);
	// Create a blank pixmap to hold the result of rendering. The
	// pixmap bounds used here are the same as the transformed page
	// bounds, so it will contain the entire page. The page coordinate
	// space has the origin at the top left corner and the x axis
	// extends to the right and the y axis extends down.

	fz_irect bbox;
	fz_round_rect(&bbox, &bounds);
	fz_pixmap *pix = fz_new_pixmap_with_bbox(ctx, fz_device_rgb(ctx), &bbox);
	fz_clear_pixmap_with_value(ctx, pix, 0xff);

	// A page consists of a series of objects (text, line art, images,
	// gradients). These objects are passed to a device when the
	// interpreter runs the page. There are several devices, used for
	// different purposes:
	//
	//	draw device -- renders objects to a target pixmap.
	//
	//	text device -- extracts the text in reading order with styling
	//	information. This text can be used to provide text search.
	//
	//	list device -- records the graphic objects in a list that can
	//	be played back through another device. This is useful if you
	//	need to run the same page through multiple devices, without
	//	the overhead of parsing the page each time.

	// Create a draw device with the pixmap as its target.
	// Run the page with the transform.
	fz_device *dev = fz_new_draw_device(ctx, pix);
	pdf_run_annot(pdoc,(pdf_page*)page,wid1,dev,&tran,NULL);
	fz_run_page(doc, page, dev, &transform, NULL);
	fz_free_device(dev);
    unsigned char * data;
    bitmap = RGBAtoBitmap(pix->samples,pix->w,pix->h);
    w = bitmap->GetWidth();
    h = bitmap->GetHeight();
    SetScrollbars(1,1,w,h,0,0);
//bitmap = wxBitmap((const char*)data,pix->w,pix->h,32);
	// Clean up.
    pdf_page_write(pdoc,(pdf_page*)page);
	fz_drop_pixmap(ctx, pix);
	fz_free_page(doc, page);
	fz_close_document(doc);
	fz_free_context(ctx);
	Refresh();
}
*/
void PDFPanel::OnClick(wxMouseEvent &event)
{
    //Selected Fields cannot be more than 50 at a page
    if(selectedItems.size() > 50)
    {
        wxMessageBox(wxT("No more fields can be selected"));
        return;
    }
    wxPoint pt1,pt;
    pt1 = CalcUnscrolledPosition(event.GetPosition());
    pt1.x *= scale;
    pt1.y *= scale;
    Field f = doc32->SelectField(pt1);
    it = selectedItems.begin();
    while(it!=selectedItems.end())
    {
        if(it->id == f.id)
            return;
        it++;
    }
    if(strcmp(f.name,"empty"))
    {
        int x0 = f.xPos/scale;
        int y0 = f.yPos/scale;
        int width = f.width/scale;
        int height = f.height/scale;
        selectedItems.push_back(SelectedItem(wxRect(x0,y0,width,height),f.id));
    }
    else
    {
        selectedItems.clear();

    }
    Refresh();
}

int PDFPanel::GetPageCount()
{
    return doc32->getPageCount();
}

void PDFPanel::Zoom(int zm)
{
    SetFocus();
    float oldScale = scale;
    doc32->setCurZoom(zm);
    bitmap = doc32->renderPDF();
    w = bitmap->GetWidth();
    h = bitmap->GetHeight();
    grid.SetWidth((float)w);
    grid.SetHeight((float)h);
    //Updating the Scale Based on new dimensions
    scale = (float)doc32->getPDFHeight()/h;
    UpdateVisualSelection(oldScale);
    SetScrollbars(1,1,w,h,0,0);
    SetScrollRate(10,10);
    Refresh();
}

void PDFPanel::ChangePage(int num)
{
    wxBusyCursor wait;
    selectedItems.clear();
    SetFocus();
    doc32->setCurPage(num);
    doc32->LoadPage(doc32->getCurPage());
    bitmap = doc32->renderPDF();
    w = bitmap->GetWidth();
    h = bitmap->GetHeight();
    scale = (float)doc32->getPDFHeight()/h;
    SetScrollbars(1,1,w,h,0,0);
    SetScrollRate(10,10);
    Refresh();
}


void PDFPanel::DropField(wxCoord x,wxCoord y,wxString data)
{
    selectedItems.clear();
    wxBusyCursor wait;
    wxPoint pt,pt1;
    pt = wxPoint(x,y);
    pt1 = CalcUnscrolledPosition(pt);
    x = pt1.x;
    y =  pt1.y;
    Field f;
    f.height = 20;
    f.width = 100;
    f.pageNo = 0;
    f.xPos = x*scale;
    f.yPos = y*scale;
    f.value = "IAMAWESOME";
    char * temp = "D";
    f.name = temp;
    doc32->AddField(f);
    doc32->LoadPage(doc32->getCurPage());
    bitmap = doc32->renderPDF();
//    w = bitmap->GetWidth();
//    h = bitmap->GetHeight();
    Refresh();
}

void PDFPanel::displayFieldValues(bool val)
{
    SetFocus();
    doc32->setDemo(val);
    bitmap = doc32->renderPDF();
    Refresh();
}

void PDFPanel::DisplayGrid(bool val)
{
    SetFocus();
    grid.SetGridDisplay(val);
    Refresh();
}

void PDFPanel::AlignFields()
{
    SetFocus();
    if(selectedItems.size()>0 && grid.GetDisplay())
    {
        doc32->AlignSelectedField(grid,selectedItems,scale);
        bitmap = doc32->renderPDF();
        Refresh();
    }
}

void PDFPanel::UpdateVisualSelection(float oldScale)
{
    it = selectedItems.begin();
    while(it!=selectedItems.end())
    {
        it->rect.x = (it->rect.x * oldScale)/scale;
        it->rect.y = (it->rect.y * oldScale)/scale;
        it->rect.height = (it->rect.height * oldScale)/scale;
        it->rect.width = (it->rect.width * oldScale)/scale;
        it++;
    }
}

void PDFPanel::OnKeyPressed(wxKeyEvent &event)
{
    if(selectedItems.size()>0)
    {
        switch(event.GetKeyCode())
        {
        case WXK_LEFT:
            doc32->MoveFields(wxPoint(-1,0),selectedItems,scale);
            bitmap = doc32->renderPDF();
            Refresh();
            break;
        case WXK_RIGHT:
            doc32->MoveFields(wxPoint(1,0),selectedItems,scale);
            bitmap = doc32->renderPDF();
            Refresh();
            break;
        case WXK_UP:
            doc32->MoveFields(wxPoint(0,-1),selectedItems,scale);
            bitmap = doc32->renderPDF();
            Refresh();
            break;
        case WXK_DOWN:
            doc32->MoveFields(wxPoint(0,1),selectedItems,scale);
            bitmap = doc32->renderPDF();
            Refresh();
            break;
        }
    }
}


temp::temp(PDFPanel *win)
{
    window = win;
}

bool temp::OnDropText(wxCoord x, wxCoord y, const wxString &data)
{
   window->DropField(x,y,data);
}

