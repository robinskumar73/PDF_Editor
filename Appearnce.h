#ifndef _APPEARANCE_H
#define _APPEARANCE_H

extern "C"
{
        #include <mupdf/fitz.h>
        #include<mupdf/pdf.h>
}


class Appearance
{
    //CheckBox Appearance
    void CheckboxAppearance(pdf_document * pdoc,pdf_annot * widget);

    void InitCheckboxPath(fz_context * ctx, fz_path * box,fz_path * tick);

    void SetOnAppearance(pdf_document *doc, pdf_annot *annot, fz_rect *rect, fz_display_list *disp_list);

    void SetOffAppearance(pdf_document *doc, pdf_annot *annot, fz_rect *rect, fz_display_list *disp_list);

    void rect_center(const fz_rect *rect, fz_point *c);

    void center_rect_within_rect(const fz_rect *tofit, const fz_rect *within, fz_matrix *mat);

public:
     //Creating Default Appearances for the Fields
    void CreateAppearance(pdf_document * pdoc,pdf_annot * widget);


};
#endif // _APPEARANCE_H
