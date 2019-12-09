package sample;

import javafx.application.Application;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.fxml.FXMLLoader;
import javafx.geometry.Insets;
import javafx.geometry.Pos;
import javafx.geometry.Side;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.chart.BarChart;
import javafx.scene.chart.CategoryAxis;
import javafx.scene.chart.NumberAxis;
import javafx.scene.chart.XYChart;
import javafx.scene.control.*;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.scene.layout.HBox;
import javafx.scene.layout.Pane;
import javafx.scene.layout.VBox;
import javafx.scene.text.Text;
import javafx.stage.Stage;

public class Main extends Application {
    public class Person {
        public String name;
        public Integer korean;
        public Integer math;
        public Integer english;

        public Person(String name, Integer korean, Integer math, Integer english) {
            this.name = name;
            this.korean = korean;
            this.math = math;
            this.english = english;
        }

        public Person() {
        }

        public String getName() {
            return name;
        }

        public void setName(String name) {
            this.name = name;
        }

        public Integer getKorean() {
            return korean;
        }

        public void setKorean(Integer korean) {
            this.korean = korean;
        }

        public Integer getMath() {
            return math;
        }

        public void setMath(Integer math) {
            this.math = math;
        }

        public Integer getEnglish() {
            return english;
        }

        public void setEnglish(Integer english) {
            this.english = english;
        }
    }

    @Override
    public void start(Stage primaryStage) throws Exception {
        VBox box = new VBox();

        ObservableList<Person> tableData = FXCollections.observableArrayList();
        TableView table = new TableView();
        TableColumn nameCol = new TableColumn("이름");
        TableColumn koreanCol = new TableColumn("국어");
        TableColumn mathCol = new TableColumn("수학");
        TableColumn englishCol = new TableColumn("영어");
        nameCol.setCellValueFactory(new PropertyValueFactory<Person, String>("name"));
        koreanCol.setCellValueFactory(new PropertyValueFactory<Person, Integer>("korean"));
        mathCol.setCellValueFactory(new PropertyValueFactory<Person, Integer>("math"));
        englishCol.setCellValueFactory(new PropertyValueFactory<Person, Integer>("english"));
        nameCol.setStyle("-fx-alignment: CENTER;");
        koreanCol.setStyle("-fx-alignment: CENTER;");
        mathCol.setStyle("-fx-alignment: CENTER;");
        englishCol.setStyle("-fx-alignment: CENTER;");
        table.getColumns().addAll(nameCol, koreanCol, mathCol, englishCol);
        table.setItems(tableData);

        tableData.add(new Person("홍길동A", 40, 60, 80));
        tableData.add(new Person("홍길동B", 60, 80, 40));
        tableData.add(new Person("홍길동C", 80, 40, 60));

        Button btn = new Button("추가");
        btn.setOnAction((e) -> {
            Stage stage = new Stage();
            stage.setTitle("추가");

            VBox vbox = new VBox();
            vbox.setPadding(new Insets(30));

            Scene scene = new Scene(vbox);

            Label lbName = new Label("이름");
            Label lbKorean = new Label("국어");
            Label lbMath = new Label("수학");
            Label lbEnglish = new Label("영어");

            int lbPadding = 40;
            lbName.setPadding(new Insets(0, lbPadding, 0, 0));
            lbKorean.setPadding(new Insets(0, lbPadding, 0, 0));
            lbMath.setPadding(new Insets(0, lbPadding, 0, 0));
            lbEnglish.setPadding(new Insets(0, lbPadding, 0, 0));

            TextField tbName = new TextField();
            TextField tbKorean = new TextField();
            TextField tbMath = new TextField();
            TextField tbEnglish = new TextField();

            int tbWidth = 200;
            tbName.setPrefWidth(tbWidth);
            tbKorean.setPrefWidth(tbWidth);
            tbMath.setPrefWidth(tbWidth);
            tbEnglish.setPrefWidth(tbWidth);

            Button btnAdd = new Button("저장");
            Button btnCancel = new Button("취소");

            btnAdd.setOnAction((eventBtnAdd) -> {
                Person p = new Person();
                p.name = tbName.getText();
                p.korean = Integer.parseInt(tbKorean.getText());
                p.math = Integer.parseInt(tbMath.getText());
                p.english = Integer.parseInt(tbEnglish.getText());
                tableData.add(p);
                stage.close();
            });

            btnCancel.setOnAction((eventBtnCancel) -> {
                stage.close();
            });

            HBox hbox1 = new HBox();
            HBox hbox2 = new HBox();
            HBox hbox3 = new HBox();
            HBox hbox4 = new HBox();
            HBox hbox5 = new HBox();

            hbox1.getChildren().addAll(lbName, tbName);
            hbox2.getChildren().addAll(lbKorean, tbKorean);
            hbox3.getChildren().addAll(lbMath, tbMath);
            hbox4.getChildren().addAll(lbEnglish, tbEnglish);
            hbox5.getChildren().addAll(btnAdd, btnCancel);
            hbox5.setAlignment(Pos.CENTER);
            hbox5.setPadding(new Insets(15, 0, 0, 0));

            vbox.setSpacing(5);
            vbox.getChildren().addAll(hbox1, hbox2, hbox3, hbox4, hbox5);
            stage.setScene(scene);
            stage.show();
        });

        Button btnGraph = new Button("학생별 막대그래프");
        btnGraph.setOnAction((eventBtnGraph) -> {
            Stage stage = new Stage();
            stage.setTitle("막대 그래프");
            VBox vbox = new VBox();
            vbox.setSpacing(25);
            vbox.setPadding(new Insets(15));
            Scene scene = new Scene(vbox);
            stage.setScene(scene);

            CategoryAxis xAxis = new CategoryAxis();
            NumberAxis yAxis = new NumberAxis();
            BarChart<String, Number> chart = new BarChart<String, Number>(xAxis, yAxis);
            chart.setLegendSide(Side.BOTTOM);
            XYChart.Series koreanSeries = new XYChart.Series();
            XYChart.Series mathSeries = new XYChart.Series();
            XYChart.Series englishSeries = new XYChart.Series();
            koreanSeries.setName("국어");
            mathSeries.setName("수학");
            englishSeries.setName("영어");
            for (Person p : tableData) {
                koreanSeries.getData().add(new XYChart.Data(p.getName(), p.getKorean()));
                mathSeries.getData().add(new XYChart.Data(p.getName(), p.getMath()));
                englishSeries.getData().add(new XYChart.Data(p.getName(), p.getEnglish()));
            }
            chart.getData().addAll(koreanSeries, mathSeries, englishSeries);

            Button btnClose = new Button("닫기");
            btnClose.setOnAction((eventBtnClose) -> {
                stage.close();
            });

            vbox.setAlignment(Pos.CENTER);
            vbox.getChildren().addAll(chart, btnClose);
            stage.show();
        });

        HBox hbox = new HBox(btn, btnGraph);
        hbox.setAlignment(Pos.CENTER);
        hbox.setSpacing(20);

        box.setSpacing(20);
        box.setPadding(new Insets(0, 0, 20, 0));
        box.setAlignment(Pos.CENTER);
        box.getChildren().add(table);
        box.getChildren().add(hbox);

        Scene scene = new Scene(box);
        primaryStage.setScene(scene);
        primaryStage.setTitle("AppMain");
        primaryStage.show();
    }

    public static void main(String[] args) {
        launch(args);
    }
}
