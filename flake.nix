{
  description = "MerrinX dwm build";

  inputs.nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";

  outputs = {
    self,
    nixpkgs,
  }: let
    system = "x86_64-linux";
    pkgs = import nixpkgs {inherit system;};
    overlay = final: prev: {
      dwm = prev.dwm.overrideAttrs (old: {
        src = builtins.path {
          path = ./.;
          name = "dwm";
        };
        buildInputs =
          old.buildInputs
          ++ [
            prev.imlib2
          ];
      });
    };
  in {
    devShells.x86_64-linux.default = pkgs.mkShell {
      name = "dwm-dev";
      packages = with pkgs; [
        gcc
        pkgconfig
        imlib2
        xorg.libX11
        xorg.libXft
        xorg.libXinerama
      ];
    };

    overlays.default = overlay;
    checks.${system}.build =
      (
        import nixpkgs {
          inherit system;
          overlays = [overlay];
        }
      )
      .dwm;
  };
}
