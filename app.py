import streamlit as st

st.set_page_config(page_title="Tic-Tac-Toe", page_icon="🎮", layout="centered")

st.title("🎮 Tic-Tac-Toe")
st.caption("Play against a friend or challenge the Minimax AI.")

if "board" not in st.session_state:
    st.session_state.board = [" "] * 9
if "game_mode" not in st.session_state:
    st.session_state.game_mode = "Player vs AI"
if "turn" not in st.session_state:
    st.session_state.turn = "X"


def winner(board):
    wins = [(0,1,2),(3,4,5),(6,7,8),(0,3,6),(1,4,7),(2,5,8),(0,4,8),(2,4,6)]
    for a, b, c in wins:
        if board[a] != " " and board[a] == board[b] == board[c]:
            return board[a]
    if " " not in board:
        return "T"
    return "N"


def minimax(board, ai_turn):
    result = winner(board)
    if result == "O": return 10
    if result == "X": return -10
    if result == "T": return 0

    scores = []
    for i in range(9):
        if board[i] == " ":
            board[i] = "O" if ai_turn else "X"
            scores.append((minimax(board, not ai_turn), i))
            board[i] = " "
    return max(scores)[0] if ai_turn else min(scores)[0]


def best_move(board):
    best_score = -1000
    move = None
    for i in range(9):
        if board[i] == " ":
            board[i] = "O"
            score = minimax(board, False)
            board[i] = " "
            if score > best_score:
                best_score, move = score, i
    return move


def reset():
    st.session_state.board = [" "] * 9
    st.session_state.turn = "X"

mode = st.radio("Game Mode", ["Player vs AI", "2 Players"], horizontal=True)
if mode != st.session_state.game_mode:
    st.session_state.game_mode = mode
    reset()

result = winner(st.session_state.board)
if result == "N":
    if mode == "Player vs AI" and st.session_state.turn == "O":
        move = best_move(st.session_state.board)
        if move is not None:
            st.session_state.board[move] = "O"
            st.session_state.turn = "X"
        st.rerun()
    else:
        player_name = "Player X" if st.session_state.turn == "X" else "Player O"
        st.info(f"{player_name}'s turn")

cols = st.columns(3)
for i in range(9):
    with cols[i % 3]:
        label = st.session_state.board[i] if st.session_state.board[i] != " " else " "
        if st.button(label, key=f"cell_{i}", use_container_width=True):
            if winner(st.session_state.board) == "N" and st.session_state.board[i] == " ":
                st.session_state.board[i] = st.session_state.turn
                st.session_state.turn = "O" if st.session_state.turn == "X" else "X"
                st.rerun()

result = winner(st.session_state.board)
if result == "X":
    st.success("🏆 Player X wins!")
elif result == "O":
    st.success("🏆 Player O / AI wins!")
elif result == "T":
    st.warning("🤝 It's a tie!")

if st.button("🔄 New Game", use_container_width=True):
    reset()
    st.rerun()

st.divider()
st.caption("Built with Python + Streamlit. AI mode uses the Minimax algorithm, matching the original C++ project.")
