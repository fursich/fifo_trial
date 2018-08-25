shared_examples 'queue' do
  describe '#initialize' do
    subject { base_queue }

    it "initializes its length with 0" do
      expect(subject.length).to eq 0
    end
  end

  describe '#push' do
    subject { base_queue }

    it "returns base_queue" do
      expect( subject.push(:foo) ).to eq base_queue
    end

    it "changes its length by 1" do
      expect{ subject.push(:foo) }.to change { subject.length }.by(1)
    end

    context "when pushing :foo element" do
      before do
        @queue = base_queue.push(:foo)
      end

      describe '#value' do
        subject { @queue.value }
        it { is_expected.to eq :foo }
      end

      describe '#length' do
        subject { @queue.length }
        it { is_expected.to eq 1 }
      end

      context "when pushing 'bar' element" do
        before do
          @queue = base_queue.push('bar')
        end

        describe '#value' do
          subject { @queue.value }
          it { is_expected.to eq 'bar' }
        end

        describe '#length' do
          subject { @queue.length }
          it { is_expected.to eq 2 }
        end
      end
    end
  end

  describe '#pop' do
    subject { base_queue }

    it "returns nil" do
      expect( subject.pop ).to eq nil
    end

    it "keeps its length unchanged" do
      expect{ subject.pop }.not_to change { subject.length }
    end

    context "when pushing :foo element" do
      before do
        base_queue.push(:foo)
      end

      it "returns :foo" do
        expect( subject.pop ).to eq :foo
      end

      it "decreases its length by 1" do
        expect{ subject.pop }.to change { subject.length }.by(-1)
      end

      context "when popped" do
        before do
          base_queue.pop
        end

        describe '#value' do
          subject { base_queue.value }
          it { is_expected.to eq nil }
        end

        describe '#length' do
          subject { base_queue.length }
          it { is_expected.to eq 0 }
        end

        context "when popped twice" do
          it "raises no error(s)" do
            expect{ subject.pop }.not_to raise_error
          end

          it "returns nil" do
            expect( subject.pop ).to eq nil
          end

          it "keeps its length unchanged" do
            expect{ subject.pop }.not_to change { subject.length }
          end
        end
      end

      context "when pushing 'bar' element" do
        before do
          base_queue.push('bar')
        end

        it "returns 'bar'" do
          expect( subject.pop ).to eq 'bar'
        end

        it "decreases its length by 1" do
          expect{ subject.pop }.to change { subject.length }.by(-1)
        end

        context "when popped" do
          before do
            base_queue.pop
          end

          describe '#value' do
            subject { base_queue.value }
            it { is_expected.to eq :foo }
          end

          describe '#length' do
            subject { base_queue.length }
            it { is_expected.to eq 1 }
          end

          describe '#pop' do
            subject { base_queue.pop }
            it { is_expected.to eq :foo }
          end

          context "when popped twice" do
            before do
              base_queue.pop
            end

            describe '#value' do
              subject { base_queue.value }
              it { is_expected.to eq nil }
            end

            describe '#length' do
              subject { base_queue.length }
              it { is_expected.to eq 0 }
            end
          end
        end
      end
    end
  end
end
