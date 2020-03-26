#include "bigNnumber.h"

bigNumber abs_max(bigNumber q, bigNumber qq){
    bigNumber qqq=q,qqqq=qq;
    qqq.sign=0;
    qqqq.sign=0;
    if(qqq>=qqqq)
        return q;
    return qq;
}

void bigNumber::setll(long long int q){
    sign = (q < 0);
    if(q<0)
        q=-q;
    int k=0;
    if(q==0){
        k=1;
        v[1]=0;
    }
    while(q){
        v[++k]=q%10;
        q/=10;
    }
    L=k;
}

int bigNumber::comp(bigNumber q){
    //erase0();
    //q.erase0();
    int s=1;
    if(sign>q.sign)
        return -1;
    if(q.sign>sign)
        return 1;
    if(q.sign+sign == 2)
        s=-1;
    if(L<q.L)return -1*s;
    else if (L>q.L)return 1*s;
    for(int i=L;i>=1;--i){
        if(v[i]<q.v[i])
            return -1*s;
        else if(v[i]>q.v[i])
            return 1*s;
    }
    return 0;
}

void bigNumber::erase0(){
    while(L>1 && !v[L])
        L--;
}

void bigNumber::mult10(int q){
    if(L==1 && v[1]==0)return;
    L+=q;
    for(int i=L;i>q;--i)v[i]=v[i-q];
    for(int i=1;i<=q;++i)v[i]=0;
}

void bigNumber::div10(int q){
    if( ( L -= q ) <= 0){
        L = 1;
        v[1] = 0;
        sign = 0;
    }
    else
        for(int i=1;i<=L;++i)v[i]=v[i+q];
}

bigNumber bigNumber::mult(bigNumber q){
    bigNumber res;
    if((L==1 && v[1]==0) || (q.L==1 && q.v[1]==0))
        return res;
    int maxl=((L>q.L)?L:q.L),p2=1,b1,b2;
    while(p2<maxl)p2<<=1;
    b1=L;b2=q.L;
    L=q.L=p2;
    for(int i=b1+1;i<=p2;)v[i++]=0;
    for(int i=b2+1;i<=p2;)q.v[i++]=0;
    res=mult2(q);
    L=b1;q.L=b2;
    return res;
}

bigNumber bigNumber::mult2(bigNumber q){
    bigNumber res,a,b,c,d,ac,bd;
    if(q.L==1){
        res.v[1]=v[1]*q.v[1];
        res.L=(res.v[2]=res.v[1]/10)>0?2:1;
        res.v[1]%=10;
    }
    else{
        a=*this;
        a.div10(a.L/2);
        b=*this;
        b.L/=2;
        c=q;
        c.div10(c.L/2);
        d=q;
        d.L/=2;
        ac=a.mult2(c);
        bd=b.mult2(d);
        a+=b;
        c+=d;
        res=a.mult(c);
        res-=ac+bd;
        res.mult10(q.L/2);
        ac.mult10(q.L);
        res+=ac+bd;
        while(res.L>1 && res.v[res.L]==0)
            res.L--;
    }
    return res;
}

bigNumber& bigNumber::operator=(long long int qq){
    setll(qq);
    return *this;
};

bigNumber::operator int(){
    int a=0;
    for(int i=L;i>=1;--i){
        a*=10;
        a+=v[i];
    }
    if(sign)
        a=-a;
    return a;
};

bool bigNumber::operator==(bigNumber q){
        if(!comp(q))return 1;
        return 0;
}

bool bigNumber::operator!=(bigNumber q){
    if(!comp(q))return 0;
    return 1;
}

 bool bigNumber::operator<(bigNumber q){
    if(comp(q)==-1)return 1;
    return 0;
}

 bool bigNumber::operator<=(bigNumber q){
    if(comp(q)==1)return 0;
    return 1;
}

bool bigNumber::operator>(bigNumber q){
    if(comp(q)==1)return 1;
    return 0;
}

bool bigNumber::operator>=(bigNumber q){
    if(comp(q)==-1)return 0;
    return 1;
}

bigNumber bigNumber::operator+(bigNumber qq){
    bigNumber qqq;
    if ( sign == 1 && qq.sign == 0 ){
        qqq = *this;
        qqq.sign=0;
        return ( qq - qqq );
    }
    if ( sign == 0 && qq.sign == 1 ){
        qqq = qq;
        qqq.sign=0;
        return ( *this - qqq );
    }
    if (sign + qq.sign == 2)
        qqq.sign=1;
    bool T=0;
    if(L<qq.L)
        for(int i=L+1;i<=qq.L;++i)
            v[i]=0;
    else if(qq.L<L)
        for(int i=qq.L+1;i<=L;++i)
            qq.v[i]=0;
    qqq.L=std::max(qq.L,L);
    for(int i=1;i<=qqq.L;++i){
        int o=v[i],oo=qq.v[i];
        qqq.v[i]=(v[i]+qq.v[i]+T)%10;
        T=(v[i]+qq.v[i]+T)>=10;
    }
    if(T){
        qqq.L=qqq.L+1;
        qqq.v[qqq.L]=1;
    }
    return qqq;
}

bigNumber& bigNumber::operator+=(bigNumber qq){
    *this=*this+qq;
    return *this;
}

bigNumber& bigNumber::operator++(){
    bigNumber qqq=1;
    *this=*this+qqq;
    return *this;
}

bigNumber bigNumber::operator++(int){
    bigNumber qqq=*this,qq=1;
    *this=*this+qq;
    return qqq;
}

bigNumber bigNumber::operator-(bigNumber q){
    bigNumber qqq;
    if ( sign == 1 && q.sign == 0 ){
        qqq = q;
        qqq.sign=1;
        return ( *this + qqq );
    }
    if ( (sign == 0 && q.sign == 1) || (sign + q.sign == 2) ){
        qqq = q;
        qqq.sign=0;
        return ( *this + qqq );
    }
    if (sign + q.sign == 2){
        qqq = q;
        qqq.sign=0;
        return ( *this + qqq );
    }
    int T=0;
    if(q>*this){
        qqq=*this;
        *this=q;
        q=qqq;
        qqq.sign=1;
    }
    for(int i=q.L+1;i<=L;++i)q.v[i]=0;
    for(int i=1;i<=L;++i){
        int rez=0;
        rez+=(T=(rez=(v[i]-(q.v[i]+T)))<0)?10:0;
        qqq.v[i]=rez;
    }
    qqq.L=L;
    qqq.erase0();
    return qqq;
}

bigNumber& bigNumber::operator-=(bigNumber q){
    *this=*this-q;
    return *this;
}

bigNumber& bigNumber::operator--(){
    bigNumber q=1;
    *this=*this-q;
    return *this;
}

bigNumber bigNumber::operator--(int){
    bigNumber q=*this,qq=1;
    *this=*this-qq;
    return q;
}

bigNumber bigNumber::operator*(long long int qq){
    bigNumber q;
    q.L=L;
    long long int T=0,w;
    for(int i=1;i<=L;++i){
        w=T+(v[i]*qq);
        T=w/10;
        q.v[i]=w%10;
    }
    while(T>0){
        q.v[++q.L]=T%10;
        T/=10;
    }
    return q;
}

bigNumber bigNumber::operator*(bigNumber q){
    bigNumber qq,qqq;
    qq=*this;
    qqq=q;
    qq.sign=qqq.sign=0;
    bool x=0;
    if(sign+q.sign == 1 && !(L==1 && v[1]==0) && !(q.L==1 && q.v[1]==0))
        x=1;
    qq = qq.mult(qqq);
    qq.sign=x;
    return qq;
}

bigNumber bigNumber::operator*=(long long int qq){
    *this=(*this)*qq;
    return *this;
}

bool operator==(int q, bigNumber qq){
    return (qq==q);
}

bool operator!=(int q, bigNumber qq){
    return (qq!=q);
}

bool operator<(int q, bigNumber qq){
    return (qq>=q);
}

bool operator<=(int q, bigNumber qq){
    return (qq>q);
}

bool operator>(int q, bigNumber qq){
    return (qq<=q);
}

bool operator>=(int q, bigNumber qq){
    return (qq<q);
}

bigNumber operator+(long long int q, bigNumber qq){
    return qq+q;
}

bigNumber operator-(const long long int q, bigNumber qq){
    bigNumber qqq(q);
    return qqq-qq;
}

bigNumber operator*(long long int q, bigNumber qq){
    return qq*q;
}

std::istream& operator>>(std::istream& filein, bigNumber& q){
    char *sir = new char[BNmaxLength];
    int st=0;
    filein>>sir;
    q.L=strlen(sir);
    if(sir[0]=='-'){
        q.L--;
        q.sign=1;
        st++;
    }
    for(int i=strlen(sir)-1;i>=st;--i)
        q.v[strlen(sir)-i]=(sir[i]-'0');
    q.erase0();
    return filein;
}

std::ostream& operator<<(std::ostream& fileout, const bigNumber& q){
    if(q.sign)
        fileout<<'-';
    for(int i=q.L;i>=1;--i)
        fileout<<(int)q.v[i];
    return fileout;
}

class bigVector{
    bigNumber v[100];
    int n;
public:
    bigNumber operator*(bigVector);
    friend std::istream& operator>>(std::istream&, bigVector&);
    friend std::ostream& operator<<(std::ostream&, const bigVector&);
    bigNumber absMax();
};

bigNumber bigVector::operator*(bigVector q){
    bigNumber qq;
    for(int i=1;i<=n;++i){
        qq+=v[i]*q.v[i];
    }
    return qq;
}

std::istream& operator>>(std::istream& filein, bigVector& q){
    filein>>q.n;
    for(int i=1;i<=q.n;++i)
        filein>>q.v[i];
    return filein;
}

std::ostream& operator<<(std::ostream& fileout, const bigVector& q){
    for(int i=1;i<=q.n;++i)
        fileout<<q.v[i]<<' ';
    return fileout;
}

bigNumber bigVector::absMax(){
    bigNumber qqq=0;
    for(int i=1;i<=n;++i)
        qqq = abs_max( qqq, v[i] );
    return qqq;
}
