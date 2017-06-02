Name:		mtee
Version:	1.0
Release:	1%{?dist}
Summary:	A tee utility that prepends timestamps	

License:	LGPL	
Source0:	mtee-1.0.tar.gz


%description


%prep
%setup -q


%build
%configure
make %{?_smp_mflags}


%install
make install DESTDIR=%{buildroot}


%files
%{_bindir}/mtee
%doc



%changelog

