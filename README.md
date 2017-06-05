# C4_PBL

H29前期 実践プログラミングPBL課題用

ソフトウェア構成（暫定）

Elements | Description
--- | ---
VirtualPlate | ゲームの進行状況を把握するための仮想のゲーム盤
HandSeeker | コンピューターのために有効打を探して教えてくれる子
BodyController | EV3shieldのライブラリ関係を統括してくれる子
Player | プレイヤーの操作を管轄してくれる子
HumanPlayer & ComputerPlayer | 同じプレイヤーでも、人とコンピューターでは振る舞いをしてくれる。（ポリモーフィズムでググッてね）
GameMaster | ソフト・ハード両方を統括して、ゲーム全体の進行をしてくれる子