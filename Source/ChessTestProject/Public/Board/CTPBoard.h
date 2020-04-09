#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Board/CTPBoardPiece.h"
#include "CTPBoard.generated.h"

class UMaterial;
class ACTPPawnBase;

//Struct for 2D array
USTRUCT(BlueprintType)
struct FGridRows
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "2D Array")
	TArray<UCTPBoardPiece*> Cols;

	UCTPBoardPiece* operator[] (int32 i)
	{
		return Cols[i];
	}
		
	void Add(UCTPBoardPiece* Col)
	{
		Cols.Add(Col);
	}
	
	FGridRows()
	{}
};

UCLASS()
class CHESSTESTPROJECT_API ACTPBoard : public AActor
{
	GENERATED_BODY()
	
public:	
	ACTPBoard();

	FORCEINLINE TArray<FGridRows> &GetBoardPieces() { return GridOfRows; }
	
	FORCEINLINE TArray<ACTPPawnBase*> &GetWhiteChessmen() { return WhiteChessmen; }
	
	FORCEINLINE TArray<ACTPPawnBase*> &GetBlackChessmen() { return BlackChessmen; }
	
protected:

	//BP class for BoardPiece
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "ChessBoard")
	TSubclassOf<UCTPBoardPiece> BPBoardPieceClass;
	
	//2D Array of Chess Pieces
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ChessBoard")
	TArray<FGridRows> GridOfRows;
	
	/** Filling rule(If it is empty, then the classes from the source will be used):
	 *	 1. Pawn
	 *	2. Rook
	 *	3. Knight
	 *	4. Bishop
	 *	5. Queen
	 *	6. King
	 */
	UPROPERTY(EditDefaultsOnly, Category = "ChessBoard")
	TArray<TSubclassOf<ACTPPawnBase>> BPChessmenClasses;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ChessBoard")
	TArray<ACTPPawnBase*> WhiteChessmen;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ChessBoard")
	TArray<ACTPPawnBase*> BlackChessmen;
	
	virtual void BeginPlay() override;
	
	void CreateBoard();

	void SpawnChessmen();
};
