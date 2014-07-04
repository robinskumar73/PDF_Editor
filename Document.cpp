#include"Document.h"

Document::Document(char * filename)
{
    ctx = fz_new_context(NULL, NULL, FZ_STORE_UNLIMITED);
    fz_register_document_handlers(ctx);

    bitmap = NULL;
    //Initializing Document properties
    filePath = filename;
    curPage = 1;
    curZoom = 100;
    //Set up wxPdfDocuments
    SetupPage();
    demo = false;
    docFields = new PageFields[pageCount];
    mUnits = 10;
}

void Document::AddField(Field f)
{
    //Incrementing the field Count on the page
    docFields[curPage].fieldCount++;
    //Reserve Space in Vector when required
    if(docFields[curPage].fieldCount>=docFields[curPage].capacity)
    {
        docFields[curPage].capacity+=20;
        docFields[curPage].pageFields.reserve(docFields[curPage].capacity);
    }

    docFields[curPage].pageFields.push_back(f);
}

void Document::LoadPage(int pageNum)
{
    double w1,h1,x1,y1;
    std::vector<Field> &vecFields = docFields[curPage].pageFields;
    std::vector<Field>::iterator it;

    wxPdfDocument pdf;
    pdf.SetSourceFile(filePath);
    pdf.SetFormColours(wxPdfColour(0,0,0),wxPdfColour(195,195,195),wxPdfColour(0,0,0));
    pdf.AddPage();
    int tplID = pdf.ImportPage(pageNum);
    pdf.GetTemplateBBox(tplID, x1, y1,w1, h1);
    //pdf.SetFormBorderStyle(wx)
    pdf.GetTemplateSize(tplID, w1, h1);
    pdf.SetTemplateBBox(tplID,x1,y1,w1,h1);
    pdf.UseTemplate(tplID,x1, y1, w1,h1);
    it = vecFields.begin();
    pdf.SetXY(0,0);
    pdf.SetLineWidth(0.3);
    pdf.SetFont(wxT("Times"), wxT(""), 20);
    while(it!=vecFields.end())
    {
        it->transX = 0;
        it->transY = 0;
        double x = (double)(it->xPos);
        double y = (double)(it->yPos);
        pdf.TextField(it->name, x, y, it->width, it->height,"D");
       // pdf.CheckBox(it->name,it->xPos,it->yPos,10,true);
        it++;
    }
    //Saving in a temporary file that is deleted on document close
    pdf.SaveAsFile(wxT("temp.pdf"));
    pdf.Close();
}

void Document::SetupPage()
{
    double w1=0,h1=0,x1=0,y1=0;
    wxPdfDocument pdf;
    pageCount = pdf.SetSourceFile(filePath);
    pdfUnitH = pdf.GetPageHeight();
    pdfUnitW = pdf.GetPageWidth();
    pdf.AddPage();
    pdf.SetFormBorderStyle(wxPDF_BORDER_DASHED,3);
    //pdf.Scale(72,72);
    int tplID = pdf.ImportPage(1);
    pdf.UseTemplate(tplID);
    pdf.SaveAsFile(wxT("temp.pdf"));
}

wxBitmap * Document::renderPDF()
{
    if(bitmap!=NULL)
        delete bitmap;
   // bitmap = new wxBitmap;
    std::vector<Field> &vecFields = docFields[curPage].pageFields;
    std::vector<Field>::iterator it;
    it = vecFields.begin();
    int zoom = curZoom;
    int rotation = 0;
	// Load the page we want. Page numbering starts from zero.


	fz_document *doc = fz_open_document(ctx, "temp.pdf");
	pdf_document *pdoc = pdf_specifics(doc);
	fz_page *page = fz_load_page(doc, 0);
		// Calculate a transform to use when rendering. This transform
	// contains the scale and rotation. Convert zoom percentage to a
	// scaling factor. Without scaling the resolution is 72 dpi.
    //pdf_insert_page(pdoc,(pdf_page*)page,curPage);
	fz_matrix transform;
	fz_rotate(&transform, rotation);
	fz_pre_scale(&transform, zoom / 100.0f, zoom / 100.0f);
	// Take the page bounds and transform them by the same matrix that
	// we will use to render the page.

	fz_rect bounds;
	fz_bound_page(doc, page, &bounds);
	fz_transform_rect(&bounds, &transform);

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
    fz_point pt;
    pt.x = 100;
    pt.y = 100;
	pdf_annot * wid;
	fz_display_list * dlist = fz_new_display_list(ctx);
	wid = (pdf_annot*)pdf_first_widget(pdoc,(pdf_page*)page);

	//Translation matrix which moves the fields
	fz_matrix transMat,scaleMat,resMat;;
	fz_scale(&scaleMat,curZoom/100.0f,curZoom/100.0f);
	resMat = scaleMat;
	if(demo)
    {
        while(wid!=NULL)
        {
            fz_pre_translate(&scaleMat,it->transX,it->transY);
            pdf_field_set_value(pdoc,wid->obj,it->value);
            pdf_update_text_markup_appearance(pdoc,wid,FZ_ANNOT_UNDERLINE);
            pdf_update_annot(pdoc,wid);
            pdf_run_annot(pdoc,(pdf_page*)page,wid,dev,&scaleMat,NULL);
            //pdf_set_annot_appearance(pdoc,wid,1);
            pdf_field_set_display(pdoc,wid->obj,1);
            wid = (pdf_annot*)pdf_next_widget((pdf_widget*)wid);
            scaleMat = resMat;
            it++;
        }
    }
    else
    {
        while(wid!=NULL)
        {
            fz_pre_translate(&scaleMat,it->transX,it->transY);
            pdf_field_set_value(pdoc,wid->obj,"");

            pdf_update_annot(pdoc,wid);
            pdf_run_annot(pdoc,(pdf_page*)page,wid,dev,&scaleMat,NULL);
            pdf_field_set_display(pdoc,wid->obj,1);
            wid = (pdf_annot*)pdf_next_widget((pdf_widget*)wid);
            scaleMat = resMat;
            it++;
        }
    }
   /* static int i =0;

    pdf_annot * annot = pdf_first_annot(pdoc,(pdf_page*)page);
    if(annot && i ==0)
    {

        pdf_run_annot(pdoc,(pdf_page*)page,annot,dev,&mat,NULL);
        i++;
    }*/
	fz_run_page(doc, page, dev, &transform, NULL);

	fz_free_device(dev);

	// Save the pixmap to a file.

    bitmap = RGBAtoBitmap(pix->samples,pix->w,pix->h);
       //fz_buffer * buf = fz_new_png_from_pixmap(ctx,pix);
       // *bitmap = (wxBitmap::NewFromPNGData((void*)buf->data,buf->len));
//        return &(wxBitmap::NewFromPNGData((void*)buf->data,buf->len));
        // Clean up.

	fz_drop_pixmap(ctx, pix);
	fz_free_page(doc, page);
	//pdf_close_document(pdoc);
	fz_close_document(doc);
	//fz_free_context(ctx);

	return bitmap;
}

wxBitmap *Document::RGBAtoBitmap(unsigned char *rgba, int w, int h)
{
   wxBitmap *bitmap1=new wxBitmap(w, h, 32);
   if(!bitmap1->Ok()) {
      delete bitmap1;
      return NULL;
   }

   PixelData bmdata(*bitmap1);
   if(bmdata==NULL) {
      wxLogDebug(wxT("getBitmap() failed"));
      delete bitmap1;
      return NULL;
   }

   bmdata.UseAlpha();
   PixelData::Iterator dst(bmdata);

   for(int y=0; y<h; y++) {
      dst.MoveTo(bmdata, 0, y);
      for(int x=0; x<w; x++) {
         // wxBitmap contains rgb values pre-multiplied with alpha
         unsigned char a=rgba[3];
         dst.Red()=rgba[0]*a/255;
         dst.Green()=rgba[1]*a/255;
         dst.Blue()=rgba[2]*a/255;
         dst.Alpha()=a;
         dst++;
         rgba+=4;
      }
   }
   return bitmap1;
}

Document::~Document()
{

}

int Document::getPageCount()
{
    return pageCount;
}

int Document::getCurZoom()
{
    return curZoom;
}

int Document::getCurPage()
{
    return curPage;
}

void Document::setCurPage(int pg)
{
    curPage = pg;
}

void Document::setCurZoom(int zm)
{
    curZoom = zm;
}

int Document::getPDFWidth()
{
    return pdfUnitW;
}


int Document::getPDFHeight()
{
    return pdfUnitH;
}

void Document::setDemo(bool dm)
{
    demo = dm;
}

Field Document::SelectField(wxPoint pt)
{
    int count = 0;
    if(docFields[curPage].fieldCount>0)
    {
        std::vector<Field> &vecFields = docFields[curPage].pageFields;
        std::vector<Field>::iterator it;
        it = vecFields.begin();
        while(it!=vecFields.end())
        {
            int x0 = it->xPos;
            int y0 = it->yPos;
            int x1 = it->width + x0;
            int y1 = it->height + y0;
            if(IsPointInRect(pt,x0,y0,x1,y1))
            {
                it->id = count;
                return *it;
            }

            it++;
            count++;
        }
    }
    return Field("empty");
}

void Document::MoveFields(wxPoint vec,std::vector<SelectedItem> &ID,float scale)
{
    int i = 0;
    std::vector<Field> &vecFields = docFields[curPage].pageFields;
    while(i<ID.size())
    {
        //wxMessageBox(wxString::Format("ID = %i\n%f",vecFields[ID[i].id].transY));
        float unitY = ((mUnits*vec.y)*100)/(float)curZoom;
        float unitX = ((mUnits*vec.x)*100)/(float)curZoom;
        vecFields[ID[i].id].transY += unitY;
        vecFields[ID[i].id].transX += unitX;
        vecFields[ID[i].id].xPos += (mUnits*vec.x)*scale;
        vecFields[ID[i].id].yPos += (mUnits*vec.y)*scale;
       // wxMessageBox(wxString::Format("ID = %i",(int)vecFields[ID[i].id].transY));
        ID[i].rect = wxRect(vecFields[ID[i].id].xPos/scale,vecFields[ID[i].id].yPos/scale,vecFields[ID[i].id].width/scale,vecFields[ID[i].id].height/scale);
        i++;
    }
}

void Document::AlignSelectedField(Grid g,std::vector<SelectedItem> &ID,float scale)
{
    int i = 0;
    std::vector<Field> &vecFields = docFields[curPage].pageFields;
    while(i<ID.size())
    {
        g.SnapField(vecFields[ID[i].id],scale,curZoom);
        ID[i].rect = wxRect(vecFields[ID[i].id].xPos/scale,vecFields[ID[i].id].yPos/scale,vecFields[ID[i].id].width/scale,vecFields[ID[i].id].height/scale);
        i++;
    }
}


