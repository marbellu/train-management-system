{

 inputs.flakelight.url = "github:nix-community/flakelight";

 outputs = { flakelight, ... }:
   flakelight ./. ({ lib, ... }: {

  nixpkgs.config = {
    allowUnsupportedSystem = true;
    allowUnfree = true;
  };

   devShell = pkgs: {
     packages = with pkgs; [
        qmake
        make
        just
        qt6.full
      ];
     };

     systems = lib.systems.flakeExposed;

    });
}
