#include "Appearnce.h"

void Appearance::CheckboxAppearance(pdf_document * pdoc,pdf_annot * widget)
{

}




void Appearance::InitCheckboxPath(fz_context * ctx, fz_path * box,fz_path * tick)
{
    //Constructing the Box
    fz_moveto(ctx, box, 199.0f, 315.6f);
	fz_lineto(ctx,box,250,315.6f);
	fz_lineto(ctx,box,250,265.6f);
	fz_lineto(ctx,box,199,265.6f);
	fz_lineto(ctx,box,199,315.6f);
	fz_lineto(ctx,box,250,315.6f);
	fz_closepath(ctx, box);

	//Constructing the Tick Mark
	fz_moveto(ctx, tick, 210.0f, 290.6f);
	fz_lineto(ctx,tick,220.0f,275.6f);
	fz_lineto(ctx,tick,245,310.6f);
}

void Appearance::SetOffAppearance(pdf_document *doc,pdf_annot *annot, fz_rect *rect,
                                                       fz_display_list *disp_list)
{
    fz_context *ctx = doc->ctx;
	pdf_obj *obj = annot->obj;
	const fz_matrix *page_ctm = &annot->page->ctm;
	fz_matrix ctm;
	fz_matrix mat = fz_identity;
	fz_device *dev = NULL;
	pdf_xobject *xobj = NULL;

	fz_invert_matrix(&ctm, page_ctm);

	fz_var(dev);
	fz_try(ctx)
	{
		pdf_obj *ap_obj;
		fz_rect trect = *rect;

		fz_transform_rect(&trect, &ctm);

		pdf_dict_puts_drop(obj, "Rect", pdf_new_rect(doc, &trect));

		/* See if there is a current normal appearance */
		ap_obj = pdf_dict_getp(obj, "AP/N/Off");
		if (!pdf_is_stream(doc, pdf_to_num(ap_obj), pdf_to_gen(ap_obj)))
			ap_obj = NULL;

		if (ap_obj == NULL)
		{
			ap_obj = pdf_new_xobject(doc, &trect, &mat);
			pdf_dict_putp_drop(obj, "AP/N/Off", ap_obj);
		}
		else
		{
			pdf_xref_ensure_incremental_object(doc, pdf_to_num(ap_obj));
			/* Update bounding box and matrix in reused xobject obj */
			pdf_dict_puts_drop(ap_obj, "BBox", pdf_new_rect(doc, &trect));
			pdf_dict_puts_drop(ap_obj, "Matrix", pdf_new_matrix(doc, &mat));
		}

		dev = pdf_new_pdf_device(doc, ap_obj, pdf_dict_gets(ap_obj, "Resources"), &mat);
		fz_run_display_list(disp_list, dev, &ctm, &fz_infinite_rect, NULL);
		fz_free_device(dev);

		/* Mark the appearance as changed - required for partial update */
		xobj = pdf_load_xobject(doc, ap_obj);
		if (xobj)
		{
			/* Update bounding box and matrix also in the xobject structure */
			xobj->bbox = trect;
			xobj->matrix = mat;
			xobj->iteration++;
			pdf_drop_xobject(ctx, xobj);
		}

		doc->dirty = 1;

//		update_rect(ctx, annot);
	}
	fz_catch(ctx)
	{
		fz_free_device(dev);
		fz_rethrow(ctx);
	}
}

void Appearance::SetOnAppearance(pdf_document *doc,pdf_annot *annot, fz_rect *rect,
                                                       fz_display_list *disp_list)
{
    fz_context *ctx = doc->ctx;
	pdf_obj *obj = annot->obj;
	const fz_matrix *page_ctm = &annot->page->ctm;
	fz_matrix ctm;
	fz_matrix mat = fz_identity;
	fz_device *dev = NULL;
	pdf_xobject *xobj = NULL;

	fz_invert_matrix(&ctm, page_ctm);

	fz_var(dev);
	fz_try(ctx)
	{
		pdf_obj *ap_obj;
		fz_rect trect = *rect;

		fz_transform_rect(&trect, &ctm);

		pdf_dict_puts_drop(obj, "Rect", pdf_new_rect(doc, &trect));

		/* See if there is a current normal appearance */
		ap_obj = pdf_dict_getp(obj, "AP/N/On");
		if (!pdf_is_stream(doc, pdf_to_num(ap_obj), pdf_to_gen(ap_obj)))
			ap_obj = NULL;

		if (ap_obj == NULL)
		{
			ap_obj = pdf_new_xobject(doc, &trect, &mat);
			pdf_dict_putp_drop(obj, "AP/N/On", ap_obj);
		}
		else
		{
			pdf_xref_ensure_incremental_object(doc, pdf_to_num(ap_obj));
			/* Update bounding box and matrix in reused xobject obj */
			pdf_dict_puts_drop(ap_obj, "BBox", pdf_new_rect(doc, &trect));
			pdf_dict_puts_drop(ap_obj, "Matrix", pdf_new_matrix(doc, &mat));
		}

		dev = pdf_new_pdf_device(doc, ap_obj, pdf_dict_gets(ap_obj, "Resources"), &mat);
		fz_run_display_list(disp_list, dev, &ctm, &fz_infinite_rect, NULL);
		fz_free_device(dev);

		/* Mark the appearance as changed - required for partial update */
		xobj = pdf_load_xobject(doc, ap_obj);
		if (xobj)
		{
			/* Update bounding box and matrix also in the xobject structure */
			xobj->bbox = trect;
			xobj->matrix = mat;
			xobj->iteration++;
			pdf_drop_xobject(ctx, xobj);
		}

		doc->dirty = 1;

//		update_rect(ctx, annot);
	}
	fz_catch(ctx)
	{
		fz_free_device(dev);
		fz_rethrow(ctx);
	}
}

void Appearance::rect_center(const fz_rect *rect, fz_point *c)
{
	c->x = (rect->x0 + rect->x1) / 2.0f;
	c->y = (rect->y0 + rect->y1) / 2.0f;
}

/*void Appearance::center_rect_within_rect(const fz_rect *tofit, const fz_rect *within, fz_matrix *mat)
{
    float xscale = (within->x1 - within->x0) / (tofit->x1 - tofit->x0);
	float yscale = (within->y1 - within->y0) / (tofit->y1 - tofit->y0);
	float scale = fz_min(xscale, yscale);
	fz_point tofit_center;
	fz_point within_center;
	rect_center(within, &within_center);
	rect_center(tofit, &tofit_center);

	/* Translate "tofit" to be centered on the origin
	 * Scale "tofit" to a size that fits within "within"
	 * Translate "tofit" to "within's" center
	 * Do all the above in reverse order so that we can use the fz_pre_xx functions
	fz_translate(mat, within_center.x, within_center.y);
	fz_pre_scale(mat, scale, scale);
	fz_pre_translate(mat, -tofit_center.x, -tofit_center.y);
}
*/
