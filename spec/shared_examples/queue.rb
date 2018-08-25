shared_examples 'queue' do
  describe '#initialize' do
    subject { base_queue }

    describe '#back' do
      subject { base_queue.back }
      it { is_expected.to eq nil }
    end

    describe '#front' do
      subject { base_queue.front }
      it { is_expected.to eq nil }
    end

    describe '#length' do
      subject { base_queue.length }
      it { is_expected.to eq 0 }
    end
  end

  describe '#enqueue' do
    subject { base_queue }

    it 'returns base_queue' do
      expect(subject.enqueue(:foo)).to eq base_queue
    end

    it 'increases its length by 1' do
      expect{ subject.enqueue(:foo) }.to change { subject.length }.by(1)
    end

    context 'when enqueueing :foo element' do
      before do
        base_queue.enqueue(:foo)
      end

      describe '#back' do
        subject { base_queue.back }
        it { is_expected.to eq :foo }
      end

      describe '#front' do
        subject { base_queue.front }
        it { is_expected.to eq :foo }
      end

      describe '#length' do
        subject { base_queue.length }
        it { is_expected.to eq 1 }
      end

      context "when enqueueing 'bar' element" do
        before do
          base_queue.enqueue('bar')
        end

        describe '#back' do
          subject { base_queue.back }
          it { is_expected.to eq 'bar' }
        end

        describe '#front' do
          subject { base_queue.front }
          it { is_expected.to eq :foo }
        end

        describe '#length' do
          subject { base_queue.length }
          it { is_expected.to eq 2 }
        end
      end
    end
  end

  describe '#dequeue' do
    subject { base_queue }

    it 'returns nil' do
      expect(subject.dequeue).to eq nil
    end

    it 'keeps its length unchanged' do
      expect{ subject.dequeue }.not_to change { subject.length }
    end

    context 'when enqueueing :foo element' do
      before do
        base_queue.enqueue(:foo)
      end

      it 'returns :foo' do
        expect(subject.dequeue).to eq :foo
      end

      it 'decreases its length by 1' do
        expect{ subject.dequeue }.to change { subject.length }.by(-1)
      end

      context 'when dequeued' do
        before do
          base_queue.dequeue
        end

        describe '#back' do
          subject { base_queue.back }
          it { is_expected.to eq nil }
        end

        describe '#front' do
          subject { base_queue.front }
          it { is_expected.to eq nil }
        end

        describe '#length' do
          subject { base_queue.length }
          it { is_expected.to eq 0 }
        end

        context 'when dequeued twice' do
          it 'raises no error(s)' do
            expect{ subject.dequeue }.not_to raise_error
          end

          it 'returns nil' do
            expect(subject.dequeue).to eq nil
          end

          it 'keeps its length unchanged' do
            expect{ subject.dequeue }.not_to change { subject.length }
          end
        end
      end

      context "when enqueueing 'bar' element" do
        before do
          base_queue.enqueue('bar')
        end

        it 'returns :foo' do
          expect(subject.dequeue).to eq :foo
        end

        it 'decreases its length by 1' do
          expect{ subject.dequeue }.to change { subject.length }.by(-1)
        end

        context 'when dequeued' do
          before do
            base_queue.dequeue
          end

          describe '#back' do
            subject { base_queue.back }
            it { is_expected.to eq 'bar' }
          end

          describe '#front' do
            subject { base_queue.front }
            it { is_expected.to eq 'bar' }
          end

          describe '#length' do
            subject { base_queue.length }
            it { is_expected.to eq 1 }
          end

          describe '#dequeue' do
            subject { base_queue.dequeue }
            it { is_expected.to eq 'bar' }
          end

          context 'when dequeued twice' do
            before do
              base_queue.dequeue
            end

            describe '#back' do
              subject { base_queue.back }
              it { is_expected.to eq nil }
            end

            describe '#front' do
              subject { base_queue.front }
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
