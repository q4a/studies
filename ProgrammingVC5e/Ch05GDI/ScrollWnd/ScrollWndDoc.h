// ScrollWndDoc.h : CScrollWndDoc ��Ľӿ�
//


#pragma once


class CScrollWndDoc : public CDocument {
protected: // �������л�����
    CScrollWndDoc();
    DECLARE_DYNCREATE(CScrollWndDoc)

// ����
public:

// ����
public:

// ��д
public:
    virtual BOOL OnNewDocument();
    virtual void Serialize(CArchive& ar);

// ʵ��
public:
    virtual ~CScrollWndDoc();
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
    DECLARE_MESSAGE_MAP()
};


