{
    description = "PermsCalc";

    inputs.nixpkgs.url = "nixpkgs/nixpkgs-unstable";

    outputs = { self, nixpkgs }:
        let
            # lastModifiedDate = self.lastModifiedDate or self.lastModified or "19700101";
            version = "1.0.0"; # builtins.substring 0 8 lastModifiedDate;
            supportedSystems = [
                "aarch64-darwin"
                "aarch64-linux"
                "x86_64-darwin"
                "x86_64-linux"
            ];
            forAllSystems = nixpkgs.lib.genAttrs supportedSystems;
            nixpkgsFor = forAllSystems (system: import nixpkgs { inherit system; overlays = [ self.overlays.default ]; });
        in {
            overlays.default = final: prev: {
                permscalc = with final; stdenv.mkDerivation rec {
                    name = "permscalc";
                    src = ./.;
                    buildPhase = "make permscalc";
                    installPhase = "mkdir -p $out/bin; install -t $out/bin permscalc";
                };
            };

            packages = forAllSystems (system: {
                inherit (nixpkgsFor.${system}) permscalc;
                default = self.packages.${system}.permscalc;
            });

            nixosModules.permscalc = { pkgs, ...}:
                {
                    nixpkgs.overlays = [ self.overlays ];
                    environment.systemPackages = [ pkgs.permscalc ];
                };

            checks = forAllSystems (system: with nixpkgsFor.${system}; {
                inherit (self.packages.${system}) permscalc;
                test = stdenv.mkDerivation {
                    name = "permscalc-test";
                    src = ./.;
                    buildInputs = [ permscalc ];
                    buildPhase = "make test";
                    installPhase = "mkdir -p $out";
                };
            });
        };
}